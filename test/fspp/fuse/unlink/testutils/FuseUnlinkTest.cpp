#include "FuseUnlinkTest.h"

using ::testing::Action;
using ::testing::Invoke;

void FuseUnlinkTest::Unlink(const char *filename) {
  int error = UnlinkReturnError(filename);
  EXPECT_EQ(0, error);
}

int FuseUnlinkTest::UnlinkReturnError(const char *filename) {
  auto fs = TestFS();

  auto realpath = fs->mountDir() / filename;
  int retval = ::unlink(realpath.c_str());
  if (0 == retval) {
    return 0;
  } else {
    return errno;
  }
}

Action<void(const char*)> FuseUnlinkTest::FromNowOnReturnDoesntExistOnLstat() {
  return Invoke([this](const char *filename) {
    ReturnDoesntExistOnLstat(filename);
  });
}
