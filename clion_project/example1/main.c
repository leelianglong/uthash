#include <stdio.h>
#include "headerfile/data_type_define.h"
#include "headerfile/header.h"
#include "uthash/uthash.h"

struct my_struct {
    int id;                    /* key */
    char name[10];
    UT_hash_handle hh;         /* makes this structure hashable */
};

struct my_struct* user = NULL;

void add_user(int user_id, char* name) {
    struct my_struct* s;
    HASH_FIND_INT(user, &user_id, s); // 先检查 user_id 是否以及在hash table中。不存在时，才创建节点
    if (s == NULL) {
        s = (struct my_struct*)malloc(sizeof(struct my_struct));
        s->id = user_id;
        HASH_ADD_INT(user, id, s);
    }
    strcpy(s->name, name); // 如果以及存在了，就仅仅把hash名字修改一下。

}

/* good */
void add_user_withHandle(struct my_struct **users, int user_id, char *name) {
    struct my_struct *s;

    HASH_ADD_INT( *users, id, s );
}

struct my_struct *find_user(int user_id) {
    struct my_struct *s;

    HASH_FIND_INT( user, &user_id, s );  /* s: output pointer */
    return s;
}

void delete_user(struct my_struct *delUser) {
    HASH_DEL(user, delUser);  /* user: pointer to deletee */
    free(delUser);             /* optional; it's up to you! */
}

void delete_all() {
    struct my_struct *current_user, *tmp;

    HASH_ITER(hh, user, current_user, tmp) {
        HASH_DEL(user,current_user);  /* delete; users advances to next */
        free(current_user);            /* optional- if you want to free  */
    }
}

void print_users() {
    struct my_struct *s;

    for(s=user; s != NULL; s=(struct my_struct*)(s->hh.next)) {
        printf("user id %d: name %s\n", s->id, s->name);
    }
}

int name_sort(struct my_struct *a, struct my_struct *b) {
    return strcmp(a->name,b->name);
}

int id_sort(struct my_struct *a, struct my_struct *b) {
    return (a->id - b->id);
}

void sort_by_name() {
    HASH_SORT(user, name_sort);
}

void sort_by_id() {
    HASH_SORT(user, id_sort);
}

int main() {
    char in[10];
    int id=1, running=1;
    struct my_struct *s;
    unsigned num_users;

    while (running) {
        printf(" 1. add user\n");
        printf(" 2. add/rename user by id\n");
        printf(" 3. find user\n");
        printf(" 4. delete user\n");
        printf(" 5. delete all users\n");
        printf(" 6. sort items by name\n");
        printf(" 7. sort items by id\n");
        printf(" 8. print users\n");
        printf(" 9. count users\n");
        printf("10. quit\n");
        gets(in);
        switch(atoi(in)) {
            case 1:
                printf("name?\n");
                add_user(id++, gets(in));
                break;
            case 2:
                printf("id?\n");
                gets(in); id = atoi(in);
                printf("name?\n");
                add_user(id, gets(in));
                break;
            case 3:
                printf("id?\n");
                s = find_user(atoi(gets(in)));
                printf("user: %s\n", s ? s->name : "unknown");
                break;
            case 4:
                printf("id?\n");
                s = find_user(atoi(gets(in)));
                if (s) delete_user(s);
                else printf("id unknown\n");
                break;
            case 5:
                delete_all();
                break;
            case 6:
                sort_by_name();
                break;
            case 7:
                sort_by_id();
                break;
            case 8:
                print_users();
                break;
            case 9:
                num_users=HASH_COUNT(user);
                printf("there are %u users\n", num_users);
                break;
            case 10:
                running=0;
                break;
        }
    }

    delete_all();  /* free any structures */
    return 0;
}
