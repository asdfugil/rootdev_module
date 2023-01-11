#include <pongo.h>
#include <errno.h>

char* module_name = "set_rootdev";

char* set_rootdev(const char* rootdev) {
	uint32_t len = 0;
	dt_node_t* dev = dt_find(gDeviceTree, "chosen");
	char str[256] = "<dict ID=\"0\"><key>IOProviderClass</key><string ID=\"1\">IOService</string><key>BSD Name</key><string ID=\"2\">";
	char* val = (char*)dt_prop(dev, "root-matching", &len);
	/* Only the NULL at last is counted, so 256 */
	if (strlen(str) + strlen(rootdev) + sizeof("</string></dict>") > 256) {
		errno = ENAMETOOLONG;
		return NULL;
	}
	strcat(str, rootdev);
	strcat(str, "</string></dict>");
	memset((void*)val, 0x0, 256);
	snprintf(val, 256, "%s", str);
	return val;
}

void rootdev_command(const char* cmd, char* args) {
	if (strlen(args) == 0) {
		printf("%s usage: %s <new root device like disk0s1s8>\n", cmd, cmd);
		return;
	}
	char* val = set_rootdev(args);
	printf("set new entry: %016llx: %s \n", (uint64_t)val, args);
	return;
}

void module_entry() {
	command_register("set_rootdev", "Sets root device in root-matching in the device tree", rootdev_command);
	return;
}

struct pongo_exports exported_symbols[] = {
	{.name = "_set_rootdev", .value = set_rootdev},
	NULL
};
