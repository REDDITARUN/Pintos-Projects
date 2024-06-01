#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"

//change code pa2
static void syscall_handler(struct intr_frame *); //static function parameter of type struct intr_frame
static int32_t my_user(const uint8_t *uaddr); //function my_user that takes a pointer to a constant uint8_t uaddr and returns int32_t
bool sys_write(int fd,   //sys_write that takes parameters file descriptor and buffer pointer to buffer, 
               const void *buffer, //and ret pointer to int and returns a boolean value
               unsigned size, 
               int* ret);
void sys_exit(int); //sys_exit that takes an integer parameter status
static int failing_case(void){sys_exit(-1);NOT_REACHED();}  //a static function failing_case that returns an int and calls sys_exit with a status of -1.
 //change code pa2 end

// change code pa1
// perform memory read from user space to kernel space
static int userspace_memo(void *src, 
                          void *des, 
                          size_t bytes); 
// change code pa1 end

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f) //change code pa2
{

  // change code pa1
  int syso_no ;//variable to store the system call number
  ASSERT(sizeof(syso_no)==4); //check that the size ofsyso_no is 4 bytes
  if (userspace_memo(f->esp,  //read the system call number from user space into syso_no
                   &syso_no, 
                   sizeof(syso_no)) == -1) { //system call number is in the 32-bit word at the caller's stack pointer.
      // thread_exit(); // invalid memory access, terminate the user process   //change code pa2
      failing_case(); //change code pa2
      return;
  }
  //change code pa1 end

  //change code pa2
  // printf("[DEBUG] system call, number = %d!\n",syso_no);
  switch (syso_no){//switch statement to handle different system call numbers.
    case SYS_EXIT:{
        int exit_c;//store the exit code.
        if(userspace_memo(f->esp + 4,//read the exit code from user space memory.
                           &exit_c, 
                           sizeof(exit_c))==-1){
            failing_case();
        } 
        sys_exit(exit_c);//system call to exit the current thread with the given exit code.
        NOT_REACHED();
        break;
      }
    case SYS_WRITE:{
        int fd, ret_c;//variables for file descriptor, return code, buffer, and size.
        const void *buffer;
        unsigned size;
        if(-1 == userspace_memo(f->esp + 4,//read file descriptor from user space memory.
                                &fd, 
                                4)){
          failing_case();
        }
        if(-1 == userspace_memo(f->esp + 8,//read buffer pointer from user space memory.
                                &buffer, 
                                4)){
          failing_case();
        }
        if(-1 == userspace_memo(f->esp + 12,//read size from user space memory.
                                &size, 
                                4)){
          failing_case();
        }
        if(!sys_write(fd,//execute system call to write to the file descriptor with the given buffer and size.
                      buffer, 
                      size, 
                      &ret_c)){
          thread_exit();
        }
        f->eax=(uint32_t) ret_c;//set the return value of the system call.
        break;
      }
    }
    // thread_exit ();
    // change code pa2 end

}

//change code pa2
void sys_exit(int status){//system call will exit the current thread with a given status
  printf("%s: exit(%d)\n", 
         thread_current()->name, 
         status);
  thread_exit();
}
bool sys_write(int fd,//system call to write data to a file descriptor
               const void *buffer, 
               unsigned size, 
               int* ret) {
  if(my_user((const uint8_t*)buffer)==-1){//check if the buffer is accessible in user space memory.
    thread_exit();
    return false;
  }
  if(fd==1){//write data to standard output.
    putbuf(buffer, 
           size);
    *ret = size;
    return true;
  }
  return false;
}
//change code pa2 end

// change code pa1
static int32_t 
my_user(const uint8_t *uaddr) {
  if (!((void *)uaddr<PHYS_BASE)) // check that the user pointer `uaddr` points below PHYS_BASE.
    return -1; // invalid memory access
  int res; // Read the value at the address `uaddr` into `result`.
  asm ("movl $1f, %0; movzbl %1, %0; 1:"
      : "=&a" (res) : "m" (*uaddr));
  return res;
}
static int 
userspace_memo(void *src, 
                          void *dst, 
                          size_t bytes) {
  int32_t valu;
  size_t i;
  for (i = 0; i < bytes; i++) {
    valu = my_user(src + i); // Read a byte of user memory starting at address `src + i`.
    if (valu < 0)  // If the value is negative, indicating invalid memory access, return -1.
      return -1; // invalid memory access
    *(char *)(dst + i) = valu & 0xff; // Otherwise, write the byte value to `dst`.
  }
  return (int)bytes; // Return the number of bytes read.
}
// change code pa1 end