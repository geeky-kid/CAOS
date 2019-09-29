#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/file.h> 
#include <linux/fs.h>
#include <linux/fcntl.h> 
#include <asm/uaccess.h> 
#include <uapi/asm-generic/errno-base.h>
asmlinkage long sys_sh_task_info(int mypid, char *fname){
	struct task_struct *task;
	struct file *f;
	int d;
	char str[1000], cat[200];
	d=sys_open(fname, O_WRONLY|O_CREAT, 0644);
	for_each_process(task){
		if(task->pid == mypid){
			printk("Process: %s\n", task->comm);
			strcpy(data, "Process: ");
			strcat(data, task->comm);
			strcat(data, "\n");
			
			printk("PID Number: %ld\n", (long)task->pid);
			strcat(data, "PID NUmber: ");
			sprintf(cat, "%ld\n", (long)task->pid);
			strcat(data, cat);
			
			printk("Process State: %ld\n", (long)task->state);
			strcat(data, "Process State: ");
			sprintf(cat, "%ld\n", (long)task->state);
			strcat(data, cat);
			
			printk("Priority: %ld\n", (long)task->prio);
			strcat(data, "Priority: ");
			sprintf(cat, "%ld\n", (long)task->prio);
			strcat(data, cat);
			
			if(d<0){
				return -EISDIR
			}
			f=fget(d);
			f->f_op->write(f, data, strlen(data), &f->f_pos);
		}
	}
// 	task=pid_task(find_vpid(mypid), PIDTYPE_PID);
// 	f=fopen("file.txt","w+");
// 	fprintf(f,"%s", task->comm);
// 	fprintf(f,"%d", task->pid);
// 	fprintf(f,"%l", task->state);
// 	fprintf(f,"%l", task->priority);
// 	fclose(f);
}
