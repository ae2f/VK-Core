#define SWTCH	1

#if SWTCH
#include "../vk.h"
#endif

int main(void) {
#if SWTCH
	(void)Test_VkInit();
	(void)Test_VkEnd();
#endif
	return 0;
}
