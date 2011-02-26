#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sigar.h>

struct system_stats {
	uint32_t version;
	uint32_t struct_size;
	uint32_t cpu_something;
	uint32_t memory_something;
};

int main(void)
{
	struct system_stats reply;

	while (!feof(stdin)) {
		int req;
		int rv = fread(&req, sizeof(req), 1, stdin);
		if (rv < 1)
			continue;
		if (req != 0)
			break;
		memset(&reply, 0, sizeof(reply));
		reply.version = (uint32_t)-1;
		reply.struct_size = sizeof(reply);
		fwrite(&reply, sizeof(reply), 1, stdout);
	}

	return 0;
}
