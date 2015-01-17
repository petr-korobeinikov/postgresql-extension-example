/*-------------------------------------------------------------------------
 *
 * hello_bgw.c
 *     example background worker for PostgreSQL
 *
 * Copyright (c) 2014-2015, PostgreSQL Global Development Group
 *
 * IDENTIFICATION
 *		hello_bgw/hello_bgw.c
 *
 *-------------------------------------------------------------------------
 */


#include "postgres.h"

#include "miscadmin.h"
#include "postmaster/bgworker.h"
#include "storage/ipc.h"
#include "storage/latch.h"
#include "storage/lwlock.h"
#include "storage/proc.h"
#include "storage/shmem.h"

#include "fmgr.h"
#include "utils/guc.h"

PG_MODULE_MAGIC;

void _PG_init(void);

static volatile sig_atomic_t got_sighup = false;
static volatile sig_atomic_t got_sigterm = false;

static void
hello_bgw_sighup(SIGNAL_ARGS)
{
	int			save_errno = errno;

	got_sighup = true;
	if (MyProc)
		SetLatch(&MyProc->procLatch);

	errno = save_errno;
}

static void
hello_bgw_sigterm(SIGNAL_ARGS)
{
	int			save_errno = errno;

	got_sigterm = true;
	if (MyProc)
		SetLatch(&MyProc->procLatch);

	errno = save_errno;
}

static void
hello_bgw_main(Datum main_arg)
{
	pqsignal(SIGHUP, hello_bgw_sighup);
	pqsignal(SIGTERM, hello_bgw_sigterm);

	BackgroundWorkerUnblockSignals();

	while (true)
	{
		int rc;

		rc = WaitLatch(&MyProc->procLatch,
					   WL_LATCH_SET | WL_TIMEOUT | WL_POSTMASTER_DEATH,
					   2000L);
		ResetLatch(&MyProc->procLatch);

		if (rc & WL_POSTMASTER_DEATH)
			proc_exit(1);


		if (got_sighup)
		{
			elog(LOG, "Got sighup; reload config.");

			got_sighup = false;
			ProcessConfigFile(PGC_SIGHUP);
		}


		if (got_sigterm)
		{
			elog(LOG, "Got sigterm; exiting cleanly.");

			proc_exit(0);
		}


		elog(LOG, "Hello, Background Worker!");
	}

	proc_exit(0);
}

void
_PG_init(void)
{
	BackgroundWorker worker;

	snprintf(worker.bgw_name, BGW_MAXLEN, "hello_bgw");

	worker.bgw_flags = BGWORKER_SHMEM_ACCESS;

	worker.bgw_start_time = BgWorkerStart_PostmasterStart;
	worker.bgw_restart_time = BGW_NEVER_RESTART;

	worker.bgw_main = hello_bgw_main;
	worker.bgw_main_arg = (Datum) 0;

#if PG_VERSION_NUM >= 90400
	worker.bgw_notify_pid = 0;
#endif

	RegisterBackgroundWorker(&worker);
}
