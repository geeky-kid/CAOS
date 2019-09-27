#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/fs.h> 
#include <stdio.h>
#include <stdlib.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>
#include <linux/pid.h>
asmlinkage long sys_sh_task_info(imt mypid, FILE *f){
	struct task_struct *task;
	task=pid_task(find_vpid(mypid), PIDTYPE_PID);
	f=fopen("file.txt","w+");
	fprintf(f,"%s", task->comm);
	fprintf(f,"%d", task->pid);
	fprintf(f,"%l", task->state);
	fprintf(f,"%l", task->priority);
	fclose(f);
}