
int rawhid_open(int max, int vid, int pid, uintmax_t usage_page, uintmax_t usage);
int rawhid_recv(int num, char *buf, int len, int timeout);
int rawhid_send(int num, char *buf, int len, int timeout);
void rawhid_close(int num);

