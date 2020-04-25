
SystemCall.ko：     文件格式 elf64-x86-64


Disassembly of section .text:

0000000000000000 <sys_mycall_victim>:
   0:	e8 00 00 00 00       	callq  5 <sys_mycall_victim+0x5>
   5:	55                   	push   %rbp
   6:	48 89 e5             	mov    %rsp,%rbp
   9:	48 83 ec 10          	sub    $0x10,%rsp
   d:	0f b6 97 00 00 00 00 	movzbl 0x0(%rdi),%edx
  14:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  18:	0f ae f0             	mfence 
  1b:	48 c7 c1 00 00 00 00 	mov    $0x0,%rcx
  22:	0f ae 39             	clflush (%rcx)
  25:	0f ae f0             	mfence 
  28:	48 8d 4d f0          	lea    -0x10(%rbp),%rcx
  2c:	0f ae 39             	clflush (%rcx)
  2f:	0f ae f0             	mfence 
  32:	8b 05 00 00 00 00    	mov    0x0(%rip),%eax        # 38 <sys_mycall_victim+0x38>
  38:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  3c:	76 15                	jbe    53 <sys_mycall_victim+0x53>
  3e:	48 c1 e2 0c          	shl    $0xc,%rdx
  42:	81 e2 00 f0 0f 00    	and    $0xff000,%edx
  48:	0f b6 84 16 00 00 00 	movzbl 0x0(%rsi,%rdx,1),%eax
  4f:	00 
  50:	88 45 ff             	mov    %al,-0x1(%rbp)
  53:	c9                   	leaveq 
  54:	c3                   	retq   

Disassembly of section .text.unlikely:

0000000000000000 <sys_mycall_help>:
   0:	e8 00 00 00 00       	callq  5 <sys_mycall_help+0x5>
   5:	55                   	push   %rbp
   6:	48 89 fe             	mov    %rdi,%rsi
   9:	48 89 e5             	mov    %rsp,%rbp
   c:	41 54                	push   %r12
   e:	49 89 fc             	mov    %rdi,%r12
  11:	48 c7 c7 00 00 00 00 	mov    $0x0,%rdi
  18:	e8 00 00 00 00       	callq  1d <sys_mycall_help+0x1d>
  1d:	49 83 fc 01          	cmp    $0x1,%r12
  21:	75 1c                	jne    3f <sys_mycall_help+0x3f>
  23:	48 c7 c6 00 00 00 00 	mov    $0x0,%rsi
  2a:	48 c7 c7 00 00 00 00 	mov    $0x0,%rdi
  31:	e8 00 00 00 00       	callq  36 <sys_mycall_help+0x36>
  36:	48 c7 c0 00 00 00 00 	mov    $0x0,%rax
  3d:	eb 41                	jmp    80 <sys_mycall_help+0x80>
  3f:	49 83 fc 02          	cmp    $0x2,%r12
  43:	75 1c                	jne    61 <sys_mycall_help+0x61>
  45:	48 c7 c6 00 00 00 00 	mov    $0x0,%rsi
  4c:	48 c7 c7 00 00 00 00 	mov    $0x0,%rdi
  53:	e8 00 00 00 00       	callq  58 <sys_mycall_help+0x58>
  58:	48 c7 c0 00 00 00 00 	mov    $0x0,%rax
  5f:	eb 1f                	jmp    80 <sys_mycall_help+0x80>
  61:	4c 89 e6             	mov    %r12,%rsi
  64:	48 c7 c7 00 00 00 00 	mov    $0x0,%rdi
  6b:	e8 00 00 00 00       	callq  70 <sys_mycall_help+0x70>
  70:	31 f6                	xor    %esi,%esi
  72:	48 c7 c7 00 00 00 00 	mov    $0x0,%rdi
  79:	e8 00 00 00 00       	callq  7e <sys_mycall_help+0x7e>
  7e:	31 c0                	xor    %eax,%eax
  80:	41 5c                	pop    %r12
  82:	5d                   	pop    %rbp
  83:	c3                   	retq   

0000000000000084 <sys_mycall_hello>:
  84:	e8 00 00 00 00       	callq  89 <sys_mycall_hello+0x5>
  89:	55                   	push   %rbp
  8a:	48 c7 c7 00 00 00 00 	mov    $0x0,%rdi
  91:	48 89 e5             	mov    %rsp,%rbp
  94:	e8 00 00 00 00       	callq  99 <sys_mycall_hello+0x15>
  99:	5d                   	pop    %rbp
  9a:	c3                   	retq   

Disassembly of section .init.text:

0000000000000000 <init_module>:
   0:	e8 00 00 00 00       	callq  5 <init_module+0x5>
   5:	55                   	push   %rbp
   6:	48 c7 c7 00 00 00 00 	mov    $0x0,%rdi
   d:	48 c7 05 00 00 00 00 	movq   $0xffffffff82000280,0x0(%rip)        # 18 <init_module+0x18>
  14:	80 02 00 82 
  18:	48 89 e5             	mov    %rsp,%rbp
  1b:	e8 00 00 00 00       	callq  20 <init_module+0x20>
  20:	48 8b 15 00 00 00 00 	mov    0x0(%rip),%rdx        # 27 <init_module+0x27>
  27:	48 8b 82 f8 06 00 00 	mov    0x6f8(%rdx),%rax
  2e:	48 89 05 00 00 00 00 	mov    %rax,0x0(%rip)        # 35 <init_module+0x35>
  35:	0f 20 c0             	mov    %cr0,%rax
  38:	89 c1                	mov    %eax,%ecx
  3a:	25 ff ff fe ff       	and    $0xfffeffff,%eax
  3f:	0f 22 c0             	mov    %rax,%cr0
  42:	48 c7 82 f8 06 00 00 	movq   $0x0,0x6f8(%rdx)
  49:	00 00 00 00 
  4d:	89 c8                	mov    %ecx,%eax
  4f:	0f 22 c0             	mov    %rax,%cr0
  52:	48 8b 82 00 07 00 00 	mov    0x700(%rdx),%rax
  59:	48 89 05 00 00 00 00 	mov    %rax,0x0(%rip)        # 60 <init_module+0x60>
  60:	0f 20 c0             	mov    %cr0,%rax
  63:	89 c1                	mov    %eax,%ecx
  65:	25 ff ff fe ff       	and    $0xfffeffff,%eax
  6a:	0f 22 c0             	mov    %rax,%cr0
  6d:	48 c7 82 00 07 00 00 	movq   $0x0,0x700(%rdx)
  74:	00 00 00 00 
  78:	89 c8                	mov    %ecx,%eax
  7a:	0f 22 c0             	mov    %rax,%cr0
  7d:	48 8b 82 08 07 00 00 	mov    0x708(%rdx),%rax
  84:	48 89 05 00 00 00 00 	mov    %rax,0x0(%rip)        # 8b <init_module+0x8b>
  8b:	0f 20 c0             	mov    %cr0,%rax
  8e:	89 c1                	mov    %eax,%ecx
  90:	25 ff ff fe ff       	and    $0xfffeffff,%eax
  95:	0f 22 c0             	mov    %rax,%cr0
  98:	89 0d 00 00 00 00    	mov    %ecx,0x0(%rip)        # 9e <init_module+0x9e>
  9e:	89 c8                	mov    %ecx,%eax
  a0:	48 c7 82 08 07 00 00 	movq   $0x0,0x708(%rdx)
  a7:	00 00 00 00 
  ab:	0f 22 c0             	mov    %rax,%cr0
  ae:	31 c0                	xor    %eax,%eax
  b0:	5d                   	pop    %rbp
  b1:	c3                   	retq   

Disassembly of section .exit.text:

0000000000000000 <cleanup_module>:
   0:	55                   	push   %rbp
   1:	48 c7 c7 00 00 00 00 	mov    $0x0,%rdi
   8:	48 89 e5             	mov    %rsp,%rbp
   b:	e8 00 00 00 00       	callq  10 <cleanup_module+0x10>
  10:	0f 20 c0             	mov    %cr0,%rax
  13:	89 c2                	mov    %eax,%edx
  15:	25 ff ff fe ff       	and    $0xfffeffff,%eax
  1a:	0f 22 c0             	mov    %rax,%cr0
  1d:	48 8b 05 00 00 00 00 	mov    0x0(%rip),%rax        # 24 <cleanup_module+0x24>
  24:	48 8b 0d 00 00 00 00 	mov    0x0(%rip),%rcx        # 2b <cleanup_module+0x2b>
  2b:	89 15 00 00 00 00    	mov    %edx,0x0(%rip)        # 31 <cleanup_module+0x31>
  31:	48 89 88 f8 06 00 00 	mov    %rcx,0x6f8(%rax)
  38:	48 8b 0d 00 00 00 00 	mov    0x0(%rip),%rcx        # 3f <cleanup_module+0x3f>
  3f:	48 89 88 00 07 00 00 	mov    %rcx,0x700(%rax)
  46:	48 8b 0d 00 00 00 00 	mov    0x0(%rip),%rcx        # 4d <cleanup_module+0x4d>
  4d:	48 89 88 08 07 00 00 	mov    %rcx,0x708(%rax)
  54:	89 d0                	mov    %edx,%eax
  56:	0f 22 c0             	mov    %rax,%cr0
  59:	5d                   	pop    %rbp
  5a:	c3                   	retq   
