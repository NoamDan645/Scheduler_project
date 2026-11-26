#include "uid.h"
#include "../tests/test_utils.h"

int main(void)
{
	uid_ty a = createUid();
	uid_ty b = createUid();

	CHECK(!UIDIsSame(a, UID_INVALID));
	CHECK(!UIDIsSame(a, b));
	CHECK(UIDIsSame(a, a));
	CHECK(b.counter == a.counter + 1);

	return TEST_RESULT("uid");
}
