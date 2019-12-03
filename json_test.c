#include <stdio.h>
#include "cJSON.h"
#include <stdlib.h>

struct node {
  int key;
  char* value[100];
  int val_inx;
  struct node* next;
};

struct node* head;
struct node* end;
struct node* Head;

int find(int key)
{
  struct node *ops = head;
  int flag = 0;
  while (ops != NULL)
  {
    if (ops->key == key)
    {
      flag = 1;
      break;
    }
    ops = ops->next;
  }
  return flag;
}

//creat key-value pair in iteration way
void printJson(cJSON * root)
{
    int i = 0;
    for(; i<cJSON_GetArraySize(root); i++)
    {
        cJSON * item = cJSON_GetArrayItem(root, i);
        if(cJSON_Object == item->type)
            printJson(item);
        else
        {
          //0 -> not find, else found
          int if_exist = find(atoi(item->string));
          //if the key has exist -> append key's value
          if (if_exist)
          {
            int virgin_loop = 1;
            struct node *ops = head;
            //locate the match key value
            while (ops != NULL)
            {
              //if matches， check wether this value appeared before
              if (ops->key == atoi(item->string))
              {
                //deduplicate
                for (int i = 0; i < sizeof(ops->value); ++i)
                {
                  //see if ops->value[i] empty -> prevent segenmetation fault
                  if (ops->value[i] == NULL)
                    break;
                  //if get a match -> skip it
                  if (0 == strcmp(ops->value[i],cJSON_Print(item)))
                  {
                    virgin_loop = 0;
                  }
                }

                if (0 == virgin_loop)
                  break;
                //if the value never appears in the key's array
                ops->value[ops->val_inx++] = cJSON_Print(item);
                break;
              }
              ops = ops->next;
            }

          }
          //if not find, apple the list
          else
          {
            if (atoi(item->string) > 1000  || atoi(item->string) < 0 )
              continue;

            struct node* node = (struct node*)malloc(sizeof(struct node));
            memset (node->value, '\0', 100);
            node->val_inx = 0;
            node->key = atoi(item->string);
            node->value[node->val_inx++] = cJSON_Print(item);

            end->next = node;
		        end = node;
          }

            // printf("%s->", item->string);
            // printf("%s\n", cJSON_Print(item));
        }
    }
}

void replace(char* str)
{
  puts(str);
  srand((unsigned)(time(NULL)));
  struct node* ops = head;
  while (ops != NULL)
  {
    int len = ops->val_inx;
    int pos = rand()%(len);
    int tmp = atoi(ops->value[pos]);
    char rp = (char)tmp;
    char array[1000000];
    strcpy(array, str);
    array[ops->key] = rp;
    str = &array[0];
    ops = ops->next;
  }
  puts(str);
}

struct node* reverseList(struct node* head) {
   if (head == NULL || head->next == NULL)
   		return head;
   	else
   	{
   		struct node * newhead = reverseList(head->next);
   		head->next->next = head;
   		head->next = NULL;
   		return newhead;
   	}
}

void show()
{
  struct node* ops = Head;
  while (1)
  {
    printf("%d: ", ops->key);
    int size = (sizeof(ops->value))/4;
    int i = 0;
    for (; i < ops->val_inx/*sizeof(ops->value)*/; ++i)
    {
        puts(ops->value[i]);
    }
    printf("\n");
    ops = ops->next;
    if (ops == end->next)
      break;
  }
}
ioMSfxtmTGKMdBCnTQ
int main(){

    FILE *f;
    long len;
    char *content;
    cJSON *json;
    head = (struct node *)malloc(sizeof(struct node));
    end = (struct node *)malloc(sizeof(struct node));
    memset (head->value, '\0', 100);
    end = head;

    f=fopen("./seed","rb");
    fseek(f,0,SEEK_END);
    len=ftell(f);
    fseek(f,0,SEEK_SET);
    content=(char*)malloc(len+1);
    fread(content,1,len,f);
    fclose(f);

    json=cJSON_Parse(content);
    if (!json) {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
    }

    printJson(json);
    // Head = reverseList(head);
    // show();
    char* string = "1232131231";
    replace(string);
    return 0;
}
