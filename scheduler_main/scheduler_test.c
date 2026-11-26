/* Runs real tasks with 1-2 second intervals, so it takes a few seconds. */
#include <string.h>

#include "scheduler.h"
#include "../tests/test_utils.h"

#define LOG_SIZE 32

static char g_log[LOG_SIZE];
static size_t g_log_len = 0;

typedef struct
{
	scheduler_ty *scheduler;
	uid_ty uid;
	char name;
	int runs_left;
} ctx_ty;

static void Log(char c)
{
	if (g_log_len < LOG_SIZE - 1)
	{
		g_log[g_log_len++] = c;
	}
}

static void ResetLog(void)
{
	g_log_len = 0;
	memset(g_log, 0, sizeof(g_log));
}

static size_t CountInLog(char c)
{
	size_t count = 0;
	size_t i = 0;

	for (i = 0; i < g_log_len; ++i)
	{
		count += (g_log[i] == c);
	}

	return count;
}

/* runs `runs_left` times, then asks to be removed */
static int Countdown(void *param)
{
	ctx_ty *ctx = (ctx_ty *)param;

	Log(ctx->name);
	return 0 == --ctx->runs_left;
}

static int StopScheduler(void *param)
{
	Log('S');
	SchedulerStop((scheduler_ty *)param);
	return 1;
}

static int RemoveSelf(void *param)
{
	ctx_ty *ctx = (ctx_ty *)param;

	Log(ctx->name);
	SchedulerRemove(ctx->scheduler, ctx->uid);
	return 0;
}

static void TestBasics(void)
{
	scheduler_ty *s = SchedulerCreate();
	ctx_ty a = {NULL, {0, 0, 0}, 'a', 1};
	uid_ty uid1, uid2;

	CHECK(NULL != s);
	CHECK(SchedulerIsEmpty(s));

	uid1 = SchedulerAdd(s, 5, Countdown, &a);
	uid2 = SchedulerAdd(s, 5, Countdown, &a);
	CHECK(!UIDIsSame(uid1, UID_INVALID));
	CHECK(!UIDIsSame(uid1, uid2));
	CHECK(2 == SchedulerSize(s));

	SchedulerRemove(s, uid1);
	CHECK(1 == SchedulerSize(s));
	SchedulerRemove(s, uid1); /* removing twice is harmless */
	CHECK(1 == SchedulerSize(s));

	SchedulerClear(s);
	CHECK(SchedulerIsEmpty(s));

	SchedulerDestroy(s);
}

static void TestRunAndRemoval(void)
{
	scheduler_ty *s = SchedulerCreate();
	ctx_ty a = {NULL, {0, 0, 0}, 'a', 3}; /* every 1s, 3 times */
	ctx_ty b = {NULL, {0, 0, 0}, 'b', 1}; /* once, after 2s */
	ctx_ty r = {NULL, {0, 0, 0}, 'r', 0}; /* removes itself */

	ResetLog();

	r.scheduler = s;
	SchedulerAdd(s, 1, Countdown, &a);
	SchedulerAdd(s, 2, Countdown, &b);
	r.uid = SchedulerAdd(s, 1, RemoveSelf, &r);

	CHECK(0 == SchedulerRun(s)); /* returns once no tasks are left */
	CHECK(SchedulerIsEmpty(s));
	CHECK(0 == a.runs_left);
	CHECK(0 == b.runs_left);
	CHECK(3 == CountInLog('a'));
	CHECK(1 == CountInLog('b'));
	CHECK(1 == CountInLog('r'));

	SchedulerDestroy(s);
}

static void TestStop(void)
{
	scheduler_ty *s = SchedulerCreate();
	ctx_ty a = {NULL, {0, 0, 0}, 'a', 100};

	ResetLog();

	SchedulerAdd(s, 1, Countdown, &a);
	SchedulerAdd(s, 2, StopScheduler, s);

	CHECK(0 == SchedulerRun(s));
	CHECK(1 == SchedulerSize(s)); /* 'a' is still scheduled */
	CHECK(1 == CountInLog('S'));
	CHECK('S' == g_log[g_log_len - 1]);

	SchedulerDestroy(s); /* frees the remaining task */
}

int main(void)
{
	TestBasics();
	TestRunAndRemoval();
	TestStop();

	return TEST_RESULT("scheduler");
}
