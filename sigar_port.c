#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sigar.h>

struct system_stats {
	uint32_t version;
	uint32_t struct_size;

	uint64_t cpu_total_ms;
	uint64_t cpu_idle_ms;

	uint64_t swap_total;
	uint64_t swap_used;
	uint64_t swap_page_in;
	uint64_t swap_page_out;

	uint64_t mem_total;
	uint64_t mem_used;
	uint64_t mem_actual_used;
	uint64_t mem_actual_free;
};

int main(void)
{
	sigar_t *sigar;
	sigar_mem_t mem;
	sigar_swap_t swap;
	sigar_cpu_t cpu;
	struct system_stats reply;

	sigar_open(&sigar);

	while (!feof(stdin)) {
		int req;
		int rv = fread(&req, sizeof(req), 1, stdin);
		if (rv < 1)
			continue;
		if (req != 0)
			break;
		memset(&reply, 0, sizeof(reply));
		reply.version = 0;
		reply.struct_size = sizeof(reply);

		sigar_mem_get(sigar, &mem);
		sigar_swap_get(sigar, &swap);
		sigar_cpu_get(sigar, &cpu);

		reply.cpu_total_ms = cpu.total;
		reply.cpu_idle_ms = cpu.idle;

		reply.swap_total = swap.total;
		reply.swap_used = swap.used;
		reply.swap_page_in = swap.page_in;
		reply.swap_page_out = swap.page_out;

		reply.mem_total = mem.total;
		reply.mem_used = mem.used;
		reply.mem_actual_used = mem.actual_used;
		reply.mem_actual_free = mem.actual_free;

		fwrite(&reply, sizeof(reply), 1, stdout);
		fflush(stdout);
	}

	return 0;
}
