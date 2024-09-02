
add.exe:     file format pei-x86-64


Disassembly of section .text:

0000000140001450 <main>:
   140001450:	55                   	push   %rbp
   140001451:	48 89 e5             	mov    %rsp,%rbp
   140001454:	48 83 ec 30          	sub    $0x30,%rsp
   140001458:	e8 f3 00 00 00       	call   140001550 <__main>
   14000145d:	c7 45 fc 01 00 00 00 	movl   $0x1,-0x4(%rbp)
   140001464:	c7 45 f8 03 00 00 00 	movl   $0x3,-0x8(%rbp)
   14000146b:	8b 55 fc             	mov    -0x4(%rbp),%edx
   14000146e:	8b 45 f8             	mov    -0x8(%rbp),%eax
   140001471:	01 d0                	add    %edx,%eax
   140001473:	89 c2                	mov    %eax,%edx
   140001475:	48 8b 05 24 2f 00 00 	mov    0x2f24(%rip),%rax        # 1400043a0 <__fu0__ZSt4cout>
   14000147c:	48 89 c1             	mov    %rax,%rcx
   14000147f:	e8 0c 00 00 00       	call   140001490 <_ZNSolsEi>
   140001484:	b8 00 00 00 00       	mov    $0x0,%eax
   140001489:	48 83 c4 30          	add    $0x30,%rsp
   14000148d:	5d                   	pop    %rbp
   14000148e:	c3                   	ret
   14000148f:	90                   	nop
