Name: Nemali Venkat Sai Abhishek
Roll Number: 213050019
CSE LDAP ID: nvsabhishek

Directions on usage of shell.c:
1. Commands are case sensitive. I made them that way for more determinism.
2. Example: The command "executeCommands" won't work in any other casings such as executecommands etc.
   It has to be exactly "executeCommands".
3. A command like ls > output.txt is taking more time than required to execute. So, if this command is in the
   file referred to by executeCommands then one might feel that the shell has got stuck in middle. But it is 
   infact running and it will complete after some time.
4. I have made the shell to be compatible with multiple operators of the same type. 
   e.g. ls | wc | cat > output.txt is also possible
5. It can take commands where operators are not space separated as well.
   e.g. ls;ps||ls|wc&&echo hello is a valid command as well.

References:
1. https://unix.stackexchange.com/questions/497543/precedence-of-pipe-and-logical-and-in-bash
2. https://man7.org/linux/man-pages/man2/read.2.html#RETURN_VALUE
3. https://man7.org/linux/man-pages/man2/write.2.html
4. https://askubuntu.com/questions/390167/how-to-clear-text-in-a-file
5. https://www.guru99.com/c-file-input-output.html
