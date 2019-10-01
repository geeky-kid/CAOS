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
	loff_t pos=0;
	mm_segment_t old_fs = get_fs();
  	set_fs(KERNEL_DS);
	d=sys_open(fname, O_WRONLY|O_CREAT, 0644);
	for_each_process(task){
		if(task->pid == mypid){
			printk("%s\n", task->comm);
			strcpy(str, "Process: ");
			strcat(str, task->comm);
			strcat(str, "\n");
			
			printk("%ld\n", (long)task->pid);
			strcat(str, "PID NUmber: ");
			sprintf(cat, "%ld\n", (long)task->pid);
			strcat(str, cat);
			
			printk("%ld\n", (long)task->state);
			strcat(str, "Process State: ");
			sprintf(cat, "%ld\n", (long)task->state);
			strcat(str, cat);
			
			printk("%ld\n", (long)task->prio);
			strcat(str, "Priority: ");
			sprintf(cat, "%ld\n", (long)task->prio);
			strcat(str, cat);
			
			if(d<0){
				return -EISDIR
			}
			f=fget(d);
			f->f_op->write(f, str, strlen(str), &f->f_pos);
		}
	}
	set_fs(old_fs);
	return 0;
}
