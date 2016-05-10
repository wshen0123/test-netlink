#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/netlink.h>
#include <net/sock.h>
#include <net/net_namespace.h>
#define NETLINK_NITRO 17

MODULE_LICENSE("GPL");

static struct sock *nl_sk = NULL;

static void nl_data_ready(struct sk_buff *skb)
{

	struct nlmsghdr *nlh = NULL;
	if (skb == NULL) {
		printk(KERN_INFO "skb is NULL \n");
		return;
	}
	nlh = (struct nlmsghdr *)skb->data;
	printk(KERN_INFO "%s: received netlink message payload: %s\n",
	       __FUNCTION__, NLMSG_DATA(nlh));
}

struct netlink_kernel_cfg cfg = {
    .input = nl_data_ready,
};

static void netlink_test(void)
{
	nl_sk = netlink_kernel_create(&init_net, NETLINK_NITRO, &cfg);
}

static int __init my_module_init(void)
{
	printk(KERN_INFO "TEST_NETLINK_MODULE INIT: Initializing Netlink Socket");
	netlink_test();
	return 0;
}

static void __exit my_module_exit(void)
{
	printk(KERN_INFO "TEST_NETLINK_MODULE FINI: Bye");
	sock_release(nl_sk->sk_socket);
}

module_init(my_module_init);
module_exit(my_module_exit);
