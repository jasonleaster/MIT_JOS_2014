// test bad pointer for user-level fault handler
// this is going to fault in the fault handler accessing eip (always!)
// so eventually the kernel kills it (PFM_KILL) because
// we outrun the stack with invocations of the user-level handler

#include <inc/lib.h>

/*
void hello()
{
    cprintf("Aha, I hack it\n");
    exit();
}
*/

void
umain(int argc, char **argv)
{
	sys_page_alloc(0, (void*) (UXSTACKTOP - PGSIZE), PTE_P|PTE_U|PTE_W);
	sys_env_set_pgfault_upcall(0, (void*) 0xDeadBeef);
	//sys_env_set_pgfault_upcall(0, (void*)hello);
	*(int*)0 = 0;
}
