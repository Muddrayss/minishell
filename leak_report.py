==236061== Memcheck, a memory error detector
==236061== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==236061== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==236061== Command: ./minishell
==236061== 
minishell: command not found: 'echa'
==236071== 
==236071== HEAP SUMMARY:
==236071==     in use at exit: 198,483 bytes in 222 blocks
==236071==   total heap usage: 711 allocs, 489 frees, 243,796 bytes allocated
==236071== 
==236071== 5 bytes in 1 blocks are still reachable in loss record 1 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x495238E: strdup (strdup.c:42)
==236071==    by 0x4AB8F4F: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 8 bytes in 1 blocks are still reachable in loss record 2 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F057: xrealloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x488A063: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x488A7D5: rl_expand_prompt (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877FE5: rl_set_prompt (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AA: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 8 bytes in 1 blocks are definitely lost in loss record 3 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x10C759: malloc_p (protected_methods.c:19)
==236071==    by 0x10A278: parser (parser.c:35)
==236071==    by 0x1096B3: minishell_loop (minishell.c:83)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 12 bytes in 1 blocks are still reachable in loss record 4 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48989E2: add_history (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109697: minishell_loop (minishell.c:81)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 13 bytes in 1 blocks are still reachable in loss record 5 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4886CF2: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4879228: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 16 bytes in 1 blocks are still reachable in loss record 6 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x4879317: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 16 bytes in 1 blocks are still reachable in loss record 7 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x10C759: malloc_p (protected_methods.c:19)
==236071==    by 0x10A4FD: init_cmd (parser.c:99)
==236071==    by 0x10A409: fill_tree (parser.c:69)
==236071==    by 0x10A2AB: parser (parser.c:39)
==236071==    by 0x1096B3: minishell_loop (minishell.c:83)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 16 bytes in 1 blocks are still reachable in loss record 8 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x10C759: malloc_p (protected_methods.c:19)
==236071==    by 0x10A4FD: init_cmd (parser.c:99)
==236071==    by 0x10A327: fill_tree (parser.c:59)
==236071==    by 0x10A44B: fill_tree (parser.c:70)
==236071==    by 0x10A2AB: parser (parser.c:39)
==236071==    by 0x1096B3: minishell_loop (minishell.c:83)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 18 bytes in 1 blocks are still reachable in loss record 9 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48782AB: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4879504: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 18 bytes in 1 blocks are still reachable in loss record 10 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4898760: alloc_history_entry (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4898A04: add_history (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109697: minishell_loop (minishell.c:81)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 20 bytes in 1 blocks are still reachable in loss record 11 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x489D56E: sh_get_home_dir (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x489E094: tilde_expand_word (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x489E2B9: tilde_expand (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4886B3A: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4886DCF: rl_read_init_file (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4879228: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 20 bytes in 1 blocks are still reachable in loss record 12 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48879D3: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4886818: rl_parse_and_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4886C6C: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4879228: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 24 bytes in 1 blocks are still reachable in loss record 13 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4898747: alloc_history_entry (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4898A04: add_history (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109697: minishell_loop (minishell.c:81)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 32 bytes in 1 blocks are still reachable in loss record 14 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x10C759: malloc_p (protected_methods.c:19)
==236071==    by 0x10D656: treenew_p (treenew_p.c:19)
==236071==    by 0x10A37A: fill_tree (parser.c:61)
==236071==    by 0x10A2AB: parser (parser.c:39)
==236071==    by 0x1096B3: minishell_loop (minishell.c:83)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 32 bytes in 1 blocks are still reachable in loss record 15 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x10C759: malloc_p (protected_methods.c:19)
==236071==    by 0x10D656: treenew_p (treenew_p.c:19)
==236071==    by 0x10A421: fill_tree (parser.c:69)
==236071==    by 0x10A2AB: parser (parser.c:39)
==236071==    by 0x1096B3: minishell_loop (minishell.c:83)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 32 bytes in 1 blocks are still reachable in loss record 16 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x10C759: malloc_p (protected_methods.c:19)
==236071==    by 0x10D656: treenew_p (treenew_p.c:19)
==236071==    by 0x10A33F: fill_tree (parser.c:59)
==236071==    by 0x10A44B: fill_tree (parser.c:70)
==236071==    by 0x10A2AB: parser (parser.c:39)
==236071==    by 0x1096B3: minishell_loop (minishell.c:83)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 32 bytes in 2 blocks are definitely lost in loss record 17 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x10C759: malloc_p (protected_methods.c:19)
==236071==    by 0x10A125: lexer_add_cmd (lexer.c:47)
==236071==    by 0x10A0AE: lexer (lexer.c:34)
==236071==    by 0x1096A3: minishell_loop (minishell.c:82)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 32 bytes in 2 blocks are definitely lost in loss record 18 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x10C759: malloc_p (protected_methods.c:19)
==236071==    by 0x10A1A6: lexer_add_token (lexer.c:58)
==236071==    by 0x10A0E0: lexer (lexer.c:37)
==236071==    by 0x1096A3: minishell_loop (minishell.c:82)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 33 bytes in 1 blocks are still reachable in loss record 19 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x4ABEFF2: _nc_read_termtype (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4ABFA8C: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4ABFE83: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4ABFFB4: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8AF5: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8F04: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071== 
==236071== 40 bytes in 1 blocks are still reachable in loss record 20 of 60
==236071==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x4AB5F2B: _nc_first_db (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4ABFF8E: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8AF5: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8F04: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 44 bytes in 1 blocks are still reachable in loss record 21 of 60
==236071==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x4ABF0A8: _nc_read_termtype (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4ABFA8C: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4ABFE83: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4ABFFB4: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8AF5: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8F04: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071== 
==236071== 44 bytes in 1 blocks are still reachable in loss record 22 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x4AB424E: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8F1B: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 63 bytes in 1 blocks are still reachable in loss record 23 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4878010: rl_set_prompt (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AA: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 63 bytes in 1 blocks are still reachable in loss record 24 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x488A02F: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x488A7D5: rl_expand_prompt (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877FE5: rl_set_prompt (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AA: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 72 bytes in 1 blocks are still reachable in loss record 25 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x4AB5E94: _nc_first_db (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4ABFF8E: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8AF5: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8F04: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 78 bytes in 1 blocks are still reachable in loss record 26 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x4AB42BF: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8F1B: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 156 bytes in 1 blocks are still reachable in loss record 27 of 60
==236071==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x4ABF140: _nc_read_termtype (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4ABFA8C: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4ABFE83: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4ABFFB4: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8AF5: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8F04: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071== 
==236071== 256 bytes in 1 blocks are still reachable in loss record 28 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4879466: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 280 bytes in 1 blocks are still reachable in loss record 29 of 60
==236071==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x4AB8EB7: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 1,024 bytes in 1 blocks are still reachable in loss record 30 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4889B8A: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x488F0E6: rl_redisplay (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48780F6: readline_internal_setup (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794D3: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 1,024 bytes in 1 blocks are still reachable in loss record 31 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4889BA0: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x488F0E6: rl_redisplay (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48780F6: readline_internal_setup (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794D3: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 1,024 bytes in 1 blocks are still reachable in loss record 32 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4889BE8: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x488F0E6: rl_redisplay (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48780F6: readline_internal_setup (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794D3: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 1,024 bytes in 1 blocks are still reachable in loss record 33 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4889C07: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x488F0E6: rl_redisplay (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48780F6: readline_internal_setup (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794D3: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 1,024 bytes in 1 blocks are still reachable in loss record 34 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4889C1F: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x488F0E6: rl_redisplay (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48780F6: readline_internal_setup (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794D3: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 1,024 bytes in 1 blocks are still reachable in loss record 35 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4889C37: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x488F0E6: rl_redisplay (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48780F6: readline_internal_setup (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794D3: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 1,536 bytes in 1 blocks are still reachable in loss record 36 of 60
==236071==    at 0x483DFAF: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F041: xrealloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487D944: rl_add_funmap_entry (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487D998: rl_initialize_funmap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487921C: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 2,032 bytes in 1 blocks are still reachable in loss record 37 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4894999: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 2,040 bytes in 1 blocks are still reachable in loss record 38 of 60
==236071==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x10C7A0: calloc_p (protected_methods.c:29)
==236071==    by 0x10C467: envp_table_init (envp_table.c:119)
==236071==    by 0x1095D3: init_data (minishell.c:53)
==236071==    by 0x1094EC: main (minishell.c:26)
==236071== 
==236071== 2,208 bytes in 138 blocks are still reachable in loss record 39 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487D8F0: rl_add_funmap_entry (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487D998: rl_initialize_funmap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487921C: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 3,312 bytes in 1 blocks are still reachable in loss record 40 of 60
==236071==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x4ABF1F8: _nc_read_termtype (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4ABFA8C: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4ABFE83: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4ABFFB4: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8AF5: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8F04: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071== 
==236071== 3,312 bytes in 1 blocks are still reachable in loss record 41 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x4AB426F: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB8F1B: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 4,016 bytes in 1 blocks are still reachable in loss record 42 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4898A5B: add_history (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109697: minishell_loop (minishell.c:81)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 4,080 bytes in 1 blocks are still reachable in loss record 43 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48949B9: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 4,112 bytes in 1 blocks are still reachable in loss record 44 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877ED9: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4879274: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 4,112 bytes in 1 blocks are still reachable in loss record 45 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877F72: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4879274: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 4,112 bytes in 1 blocks are still reachable in loss record 46 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877ED9: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4879283: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 4,112 bytes in 1 blocks are still reachable in loss record 47 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877F72: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4879283: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 4,112 bytes in 1 blocks are still reachable in loss record 48 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877ED9: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48792A1: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 4,112 bytes in 1 blocks are still reachable in loss record 49 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877F72: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48792A1: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 7,952 bytes in 1 blocks are still reachable in loss record 50 of 60
==236071==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x4AB5067: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB585F: _nc_find_type_entry (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x4AB9D9C: tgetstr_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236071==    by 0x489479B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 8,224 bytes in 2 blocks are still reachable in loss record 51 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877F63: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4879274: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 8,224 bytes in 2 blocks are still reachable in loss record 52 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877E55: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4879283: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 8,224 bytes in 2 blocks are still reachable in loss record 53 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877E55: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48792A1: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 8,224 bytes in 2 blocks are still reachable in loss record 54 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48792BF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 12,336 bytes in 3 blocks are still reachable in loss record 55 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877F3A: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4879283: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 12,336 bytes in 3 blocks are still reachable in loss record 56 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877F63: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4879283: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 12,336 bytes in 3 blocks are still reachable in loss record 57 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877F3A: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48792A1: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 12,336 bytes in 3 blocks are still reachable in loss record 58 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4877F63: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48792A1: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 12,336 bytes in 3 blocks are still reachable in loss record 59 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48792D2: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== 41,120 bytes in 10 blocks are still reachable in loss record 60 of 60
==236071==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236071==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4886A92: rl_parse_and_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4886C6C: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x4879228: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236071==    by 0x109654: minishell_loop (minishell.c:76)
==236071==    by 0x1094F6: main (minishell.c:28)
==236071== 
==236071== LEAK SUMMARY:
==236071==    definitely lost: 72 bytes in 5 blocks
==236071==    indirectly lost: 0 bytes in 0 blocks
==236071==      possibly lost: 0 bytes in 0 blocks
==236071==    still reachable: 198,411 bytes in 217 blocks
==236071==         suppressed: 0 bytes in 0 blocks
==236071== 
==236071== For lists of detected and suppressed errors, rerun with: -s
==236071== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
==236061== 
==236061== Process terminating with default action of signal 2 (SIGINT)
==236061==    at 0x48F63DB: kill (syscall-template.S:78)
==236061==    by 0x48907A2: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4892C8E: rl_getc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4893502: rl_read_key (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4878C81: readline_internal_char (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794EC: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== HEAP SUMMARY:
==236061==     in use at exit: 206,497 bytes in 454 blocks
==236061==   total heap usage: 687 allocs, 233 frees, 243,434 bytes allocated
==236061== 
==236061== 5 bytes in 1 blocks are still reachable in loss record 1 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x495238E: strdup (strdup.c:42)
==236061==    by 0x4AB8F4F: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 8 bytes in 1 blocks are still reachable in loss record 2 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10A036: lexer (lexer.c:24)
==236061==    by 0x1096A3: minishell_loop (minishell.c:82)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 8 bytes in 1 blocks are still reachable in loss record 3 of 69
==236061==    at 0x483DFAF: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F041: xrealloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x488A063: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x488A7D5: rl_expand_prompt (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877FE5: rl_set_prompt (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AA: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 8 bytes in 1 blocks are definitely lost in loss record 4 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10A278: parser (parser.c:35)
==236061==    by 0x1096B3: minishell_loop (minishell.c:83)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 12 bytes in 1 blocks are still reachable in loss record 5 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48989E2: add_history (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109697: minishell_loop (minishell.c:81)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 13 bytes in 1 blocks are still reachable in loss record 6 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4886CF2: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4879228: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 16 bytes in 1 blocks are still reachable in loss record 7 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x4879317: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 16 bytes in 1 blocks are still reachable in loss record 8 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10A1A6: lexer_add_token (lexer.c:58)
==236061==    by 0x10A0E0: lexer (lexer.c:37)
==236061==    by 0x1096A3: minishell_loop (minishell.c:82)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 16 bytes in 1 blocks are still reachable in loss record 9 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10A4FD: init_cmd (parser.c:99)
==236061==    by 0x10A409: fill_tree (parser.c:69)
==236061==    by 0x10A2AB: parser (parser.c:39)
==236061==    by 0x1096B3: minishell_loop (minishell.c:83)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 16 bytes in 1 blocks are still reachable in loss record 10 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10A4FD: init_cmd (parser.c:99)
==236061==    by 0x10A327: fill_tree (parser.c:59)
==236061==    by 0x10A44B: fill_tree (parser.c:70)
==236061==    by 0x10A2AB: parser (parser.c:39)
==236061==    by 0x1096B3: minishell_loop (minishell.c:83)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 16 bytes in 1 blocks are definitely lost in loss record 11 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10A1A6: lexer_add_token (lexer.c:58)
==236061==    by 0x10A0E0: lexer (lexer.c:37)
==236061==    by 0x1096A3: minishell_loop (minishell.c:82)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 17 bytes in 2 blocks are still reachable in loss record 12 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10A139: lexer_add_cmd (lexer.c:48)
==236061==    by 0x10A0AE: lexer (lexer.c:34)
==236061==    by 0x1096A3: minishell_loop (minishell.c:82)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 18 bytes in 1 blocks are still reachable in loss record 13 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48782AB: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4879504: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 18 bytes in 1 blocks are still reachable in loss record 14 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4898760: alloc_history_entry (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4898A04: add_history (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109697: minishell_loop (minishell.c:81)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 20 bytes in 1 blocks are still reachable in loss record 15 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x489D56E: sh_get_home_dir (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x489E094: tilde_expand_word (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x489E2B9: tilde_expand (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4886B3A: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4886DCF: rl_read_init_file (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4879228: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 20 bytes in 1 blocks are still reachable in loss record 16 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48879D3: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4886818: rl_parse_and_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4886C6C: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4879228: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 24 bytes in 1 blocks are still reachable in loss record 17 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4898747: alloc_history_entry (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4898A04: add_history (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109697: minishell_loop (minishell.c:81)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 24 bytes in 1 blocks are still reachable in loss record 18 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10CB57: lstnew_p (lstnew_p.c:19)
==236061==    by 0x10A1CC: lexer_add_token (lexer.c:61)
==236061==    by 0x10A0E0: lexer (lexer.c:37)
==236061==    by 0x1096A3: minishell_loop (minishell.c:82)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 32 bytes in 1 blocks are still reachable in loss record 19 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10D656: treenew_p (treenew_p.c:19)
==236061==    by 0x10A37A: fill_tree (parser.c:61)
==236061==    by 0x10A2AB: parser (parser.c:39)
==236061==    by 0x1096B3: minishell_loop (minishell.c:83)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 32 bytes in 1 blocks are still reachable in loss record 20 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10D656: treenew_p (treenew_p.c:19)
==236061==    by 0x10A421: fill_tree (parser.c:69)
==236061==    by 0x10A2AB: parser (parser.c:39)
==236061==    by 0x1096B3: minishell_loop (minishell.c:83)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 32 bytes in 1 blocks are still reachable in loss record 21 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10D656: treenew_p (treenew_p.c:19)
==236061==    by 0x10A33F: fill_tree (parser.c:59)
==236061==    by 0x10A44B: fill_tree (parser.c:70)
==236061==    by 0x10A2AB: parser (parser.c:39)
==236061==    by 0x1096B3: minishell_loop (minishell.c:83)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 32 bytes in 2 blocks are still reachable in loss record 22 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10A125: lexer_add_cmd (lexer.c:47)
==236061==    by 0x10A0AE: lexer (lexer.c:34)
==236061==    by 0x1096A3: minishell_loop (minishell.c:82)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 33 bytes in 1 blocks are still reachable in loss record 23 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x4ABEFF2: _nc_read_termtype (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4ABFA8C: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4ABFE83: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4ABFFB4: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8AF5: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8F04: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061== 
==236061== 40 bytes in 1 blocks are still reachable in loss record 24 of 69
==236061==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x4AB5F2B: _nc_first_db (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4ABFF8E: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8AF5: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8F04: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 44 bytes in 1 blocks are still reachable in loss record 25 of 69
==236061==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x4ABF0A8: _nc_read_termtype (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4ABFA8C: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4ABFE83: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4ABFFB4: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8AF5: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8F04: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061== 
==236061== 44 bytes in 1 blocks are still reachable in loss record 26 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x4AB424E: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8F1B: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 48 bytes in 2 blocks are still reachable in loss record 27 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10CB57: lstnew_p (lstnew_p.c:19)
==236061==    by 0x10A172: lexer_add_cmd (lexer.c:51)
==236061==    by 0x10A0AE: lexer (lexer.c:34)
==236061==    by 0x1096A3: minishell_loop (minishell.c:82)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 63 bytes in 1 blocks are still reachable in loss record 28 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4878010: rl_set_prompt (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AA: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 63 bytes in 1 blocks are still reachable in loss record 29 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x488A02F: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x488A7D5: rl_expand_prompt (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877FE5: rl_set_prompt (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AA: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 72 bytes in 1 blocks are still reachable in loss record 30 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x4AB5E94: _nc_first_db (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4ABFF8E: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8AF5: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8F04: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 78 bytes in 1 blocks are still reachable in loss record 31 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x4AB42BF: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8F1B: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 156 bytes in 1 blocks are still reachable in loss record 32 of 69
==236061==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x4ABF140: _nc_read_termtype (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4ABFA8C: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4ABFE83: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4ABFFB4: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8AF5: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8F04: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061== 
==236061== 256 bytes in 1 blocks are still reachable in loss record 33 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4879466: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 280 bytes in 1 blocks are still reachable in loss record 34 of 69
==236061==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x4AB8EB7: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 608 bytes in 1 blocks are still reachable in loss record 35 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10BFDA: env_matrix_add (envp_matrix.c:89)
==236061==    by 0x10BC4A: update_env_matrix (envp_matrix.c:27)
==236061==    by 0x10C2E1: ft_setenv (envp_table.c:65)
==236061==    by 0x10C4D5: envp_table_init (envp_table.c:127)
==236061==    by 0x1095D3: init_data (minishell.c:53)
==236061==    by 0x1094EC: main (minishell.c:26)
==236061== 
==236061== 1,024 bytes in 1 blocks are still reachable in loss record 36 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4889B8A: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x488F0E6: rl_redisplay (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48780F6: readline_internal_setup (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794D3: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 1,024 bytes in 1 blocks are still reachable in loss record 37 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4889BA0: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x488F0E6: rl_redisplay (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48780F6: readline_internal_setup (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794D3: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 1,024 bytes in 1 blocks are still reachable in loss record 38 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4889BE8: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x488F0E6: rl_redisplay (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48780F6: readline_internal_setup (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794D3: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 1,024 bytes in 1 blocks are still reachable in loss record 39 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4889C07: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x488F0E6: rl_redisplay (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48780F6: readline_internal_setup (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794D3: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 1,024 bytes in 1 blocks are still reachable in loss record 40 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4889C1F: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x488F0E6: rl_redisplay (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48780F6: readline_internal_setup (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794D3: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 1,024 bytes in 1 blocks are still reachable in loss record 41 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4889C37: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x488F0E6: rl_redisplay (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48780F6: readline_internal_setup (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794D3: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 1,200 bytes in 75 blocks are still reachable in loss record 42 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10C1F5: ft_setenv (envp_table.c:47)
==236061==    by 0x10C4D5: envp_table_init (envp_table.c:127)
==236061==    by 0x1095D3: init_data (minishell.c:53)
==236061==    by 0x1094EC: main (minishell.c:26)
==236061== 
==236061== 1,536 bytes in 1 blocks are still reachable in loss record 43 of 69
==236061==    at 0x483DFAF: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F041: xrealloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487D944: rl_add_funmap_entry (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487D998: rl_initialize_funmap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487921C: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 1,800 bytes in 75 blocks are still reachable in loss record 44 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C759: malloc_p (protected_methods.c:19)
==236061==    by 0x10CB57: lstnew_p (lstnew_p.c:19)
==236061==    by 0x10C2A5: ft_setenv (envp_table.c:64)
==236061==    by 0x10C4D5: envp_table_init (envp_table.c:127)
==236061==    by 0x1095D3: init_data (minishell.c:53)
==236061==    by 0x1094EC: main (minishell.c:26)
==236061== 
==236061== 2,032 bytes in 1 blocks are still reachable in loss record 45 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4894999: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 2,040 bytes in 1 blocks are still reachable in loss record 46 of 69
==236061==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10C7A0: calloc_p (protected_methods.c:29)
==236061==    by 0x10C467: envp_table_init (envp_table.c:119)
==236061==    by 0x1095D3: init_data (minishell.c:53)
==236061==    by 0x1094EC: main (minishell.c:26)
==236061== 
==236061== 2,208 bytes in 138 blocks are still reachable in loss record 47 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487D8F0: rl_add_funmap_entry (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487D998: rl_initialize_funmap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487921C: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 3,312 bytes in 1 blocks are still reachable in loss record 48 of 69
==236061==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x4ABF1F8: _nc_read_termtype (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4ABFA8C: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4ABFE83: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4ABFFB4: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8AF5: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8F04: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061== 
==236061== 3,312 bytes in 1 blocks are still reachable in loss record 49 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x4AB426F: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB8F1B: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB9459: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x489475B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 4,016 bytes in 1 blocks are still reachable in loss record 50 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4898A5B: add_history (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109697: minishell_loop (minishell.c:81)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 4,080 bytes in 1 blocks are still reachable in loss record 51 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48949B9: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 4,112 bytes in 1 blocks are still reachable in loss record 52 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877ED9: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4879274: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 4,112 bytes in 1 blocks are still reachable in loss record 53 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877F72: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4879274: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 4,112 bytes in 1 blocks are still reachable in loss record 54 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877ED9: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4879283: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 4,112 bytes in 1 blocks are still reachable in loss record 55 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877F72: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4879283: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 4,112 bytes in 1 blocks are still reachable in loss record 56 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877ED9: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48792A1: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 4,112 bytes in 1 blocks are still reachable in loss record 57 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877F72: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48792A1: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 4,309 bytes in 75 blocks are still reachable in loss record 58 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x10DA1A: ft_calloc (ft_calloc.c:23)
==236061==    by 0x10C076: env_matrix_add (envp_matrix.c:94)
==236061==    by 0x10BC4A: update_env_matrix (envp_matrix.c:27)
==236061==    by 0x10C2E1: ft_setenv (envp_table.c:65)
==236061==    by 0x10C4D5: envp_table_init (envp_table.c:127)
==236061==    by 0x1095D3: init_data (minishell.c:53)
==236061==    by 0x1094EC: main (minishell.c:26)
==236061== 
==236061== 7,952 bytes in 1 blocks are still reachable in loss record 59 of 69
==236061==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x4AB5067: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB585F: _nc_find_type_entry (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x4AB9D9C: tgetstr_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.2)
==236061==    by 0x489479B: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48791FF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 8,224 bytes in 2 blocks are still reachable in loss record 60 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877F63: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4879274: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 8,224 bytes in 2 blocks are still reachable in loss record 61 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877E55: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4879283: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 8,224 bytes in 2 blocks are still reachable in loss record 62 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877E55: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48792A1: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 8,224 bytes in 2 blocks are still reachable in loss record 63 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48792BF: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 12,336 bytes in 3 blocks are still reachable in loss record 64 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877F3A: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4879283: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 12,336 bytes in 3 blocks are still reachable in loss record 65 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877F63: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4879283: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 12,336 bytes in 3 blocks are still reachable in loss record 66 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877F3A: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48792A1: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 12,336 bytes in 3 blocks are still reachable in loss record 67 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4877F63: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48792A1: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 12,336 bytes in 3 blocks are still reachable in loss record 68 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4885F1D: rl_bind_keyseq_if_unbound_in_map (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48792D2: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== 41,120 bytes in 10 blocks are still reachable in loss record 69 of 69
==236061==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==236061==    by 0x489F00C: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x487DA91: rl_make_bare_keymap (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4884D79: rl_generic_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4886A92: rl_parse_and_bind (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4886C6C: ??? (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x4879228: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x48794AF: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.0)
==236061==    by 0x109654: minishell_loop (minishell.c:76)
==236061==    by 0x1094F6: main (minishell.c:28)
==236061== 
==236061== LEAK SUMMARY:
==236061==    definitely lost: 24 bytes in 2 blocks
==236061==    indirectly lost: 0 bytes in 0 blocks
==236061==      possibly lost: 0 bytes in 0 blocks
==236061==    still reachable: 206,473 bytes in 452 blocks
==236061==         suppressed: 0 bytes in 0 blocks
==236061== 
==236061== For lists of detected and suppressed errors, rerun with: -s
==236061== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
