#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

struct birthday{
    int day;
    int month;
    int year;
    struct list_head list;
};

// creates a list of birthday struct 
static LIST_HEAD(birthday_list);

int initialize(void){
    printk(KERN_INFO "Loading Module\n");
    
    // create a new object of birthday
    struct birthday * person;
    person = kmalloc(sizeof(person), GFP_KERNEL);
    person->day = 1;
    person->month = 11;
    person->year = 2000;

    INIT_LIST_HEAD(&person->list);
    int i;
    for (i = 0; i < 5; i++){
        struct birthday * newPerson;
        newPerson = kmalloc(sizeof(person), GFP_KERNEL);
        newPerson->day = 2 * i + 3;
        newPerson->month = i;
        newPerson->year = 1991 + i;
        list_add_tail(&newPerson->list, &birthday_list);
    }
    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list){
        printk(KERN_INFO "BirthDate: %d/%d/%d\n", 
        ptr->day, ptr->month, ptr->year);
    }
    return 0;
}

void exit_birth(void){
    printk(KERN_INFO "Removing Module\n");
    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list){
        list_del(&ptr->list);
        kfree(ptr);
    }
    
}

module_init(initialize);
module_exit(exit_birth);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("birth module");
MODULE_AUTHOR("SGG");