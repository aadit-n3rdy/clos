#include <stdint.h>

#include <util.h>
#include <vga.h>

extern int _kernel_start;
extern int _kernel_end;

static void* KSTART = ADDR_P2V(&_kernel_start);
static void* KEND   = ((size_t)(&_kernel_end) | 0x1fff) + 1;

#define NODE_LAST (1<<1)
#define NODE_USED (1<<0)

struct node {
	void *addr;
	size_t size;
	uint16_t next;
	uint16_t flags;
};

static struct node* nodes = (struct node*)0xFFFFF000;
static const int NODE_COUNT = 0x1000 / sizeof(struct node); // How many nodes in a page?
static struct node* head = 0;

void kmem_init() {
	vga_puts("Maximum of ");
	vga_put_uint(NODE_COUNT, 10);
	vga_puts(" nodes possible\n");
	for (int i = 0; i < NODE_COUNT; i++) {
		nodes[i].flags = 0;
	}
	nodes[0].addr = KEND;
	nodes[0].size = nodes - KEND;
	nodes[0].flags = NODE_LAST | NODE_USED;
	nodes[0].next = 0;
	head = &nodes[0];
}

static struct node* node_new() {
	for (int i = 0; i < NODE_COUNT; i++) {
		if (!(nodes[i].flags & NODE_USED)) {
			return &nodes[i];
		}
	}
	return 0;
}

static void node_free(struct node* node) {
	node->flags = 0;
}

void* kmalloc(size_t size) {
	struct node* best_fit = 0;
	struct node* cur = head;
	while (1) {
		if (cur->size >= size) {
			if (best_fit == 0 || best_fit->size > cur->size) {
				best_fit = cur;
			}
		}
		if (cur->flags & NODE_LAST)
			break;
		cur = &nodes[cur->next];
	}
}

void kfree() {
}
