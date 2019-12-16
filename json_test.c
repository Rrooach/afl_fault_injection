#include <stdio.h>
#include "cJSON.h"
#include <stdlib.h>
#include <string.h>

int key_len;
int rand_seed[1000];


struct node {
  int key;
  // char* key;
  // char* value[100];
  // int val_inx;
  struct node* next;
};

struct node* head;
struct node* end;
struct node* Head;

int find(int key)
{
  struct node *ops = head;
  int flag = 0;
  while (ops != end->next)
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
          // //0 -> not find, else found
          // int if_exist = find(atoi(item->string));
          // //if the key has exist -> append key's value
          // if (if_exist)
          // {
          //   int virgin_loop = 1;
          //   struct node *ops = head;
          //   //locate the match key value
          //   while (ops != NULL)
          //   {
          //     //if matches， check wether this value appeared before
          //     if (ops->key == atoi(item->string))
          //     {
          //       //deduplicate
          //       for (int i = 0; i < sizeof(ops->value); ++i)
          //       {
          //         //see if ops->value[i] empty -> prevent segenmetation fault
          //         if (ops->value[i] == NULL)
          //           break;
          //         //if get a match -> skip it
          //         if (0 == strcmp(ops->value[i],cJSON_Print(item)))
          //         {
          //           virgin_loop = 0;
          //         }
          //       }

          //       if (0 == virgin_loop)
          //         break;
          //       //if the value never appears in the key's array
          //       ops->value[ops->val_inx++] = cJSON_Print(item);
          //       break;
          //     }
          //     ops = ops->next;
          //   }

          // }
          // //if not find, apple the list
          // else
          // {
          //   if (atoi(item->string) > 1000  || atoi(item->string) < 0 )
          //     continue;

          //   struct node* node = (struct node*)malloc(sizeof(struct node));
          //   memset (node->value, '\0', 100);
          //   node->val_inx = 0;
          //   node->key = atoi(item->string);
          //   node->value[node->val_inx++] = cJSON_Print(item);

          //   end->next = node;
		      //   end = node;
          // }

            printf("%s->", item->string);
            printf("%s\n", cJSON_Print(item));
        }
    }
}

/* void replace(char* str)
// {
//   puts(str);
//   srand((unsigned)(time(NULL)));
//   struct node* ops = head;
//   while (ops != NULL)
//   {
//     int len = ops->val_inx;
//     int pos = rand()%(len);
//     int tmp = atoi(ops->value[pos]);
//     char rp = (char)tmp;
//     char array[1000000];
//     strcpy(array, str);
//     array[ops->key] = rp;
//     str = &array[0];
//     ops = ops->next;
//   }
//   puts(str);
// }
*/

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

// void show()
// {
//   struct node* ops = Head;
//   while (1)
//   {
//     printf("%d: ", ops->key);
//     int size = (sizeof(ops->value))/4;
//     int i = 0;
//     for (; i < ops->val_inx/*sizeof(ops->value)*/; ++i)
//     {
//         puts(ops->value[i]);
//     }
//     printf("\n");
//     ops = ops->next;
//     if (ops == end->next)
//       break;
//   }
// } 

void json_check(cJSON* root)
{ 
    char* string = "123213w1231";
    int _len = strlen(string);
    char* idx = (char*)malloc(_len+4);
    char* stemp = (char*)malloc(_len);
    memset(idx, '0', _len+4); 
    strcpy(stemp, string); 

    json_replace(root, stemp, idx);
    string = stemp;
    puts(string);
    puts(idx);
}

void json_init_key(cJSON* root)
{
  int i = 0;
  for(; i<cJSON_GetArraySize(root); i++)
  {
    cJSON * item = cJSON_GetArrayItem(root, i);
    if(cJSON_Object == item->type)
        json_init_key(item);
    else
    {  
      int if_exist = find(atoi(item->string)); 
      if (!if_exist) 
      {
        key_len++;
        if (atoi(item->string) > 1000  || atoi(item->string) < 0 )
          continue; 
        struct node* node = (struct node*)malloc(sizeof(struct node));
        // strcpy(node->key, item->string);
        node->key = atoi(item->string);
        end->next = node;
        end = node;
      } 
    }
  }
}

void json_replace(cJSON* root, char* string, char* idx)
{


  int i = 0;
  for(; i<cJSON_GetArraySize(root); i++)
  {
    cJSON * item = cJSON_GetArrayItem(root, i);
    if(cJSON_Object == item->type)
        json_replace(item, string, idx);
    else
    {   
      int _pos = atoi(item->string); 
      int int_a = atoi(cJSON_Print(item)); 
      char _val = (char)int_a; 

      if (idx[atoi(item->string)] == '0')
      { 
        string[_pos] = _val; 
        idx[_pos] = '1'; 
      }
        // printf("%s->", item->string);
        // printf("%s\n", cJSON_Print(item));
    }
  }
}


int main(){

    FILE *f;
    long len;
    char *content;
    cJSON *json = NULL; 
    /*every element in rand_seed stand for a part of ehc, eg: rand_seed[0] represent ehc 1st to 10th*/
    int key_len =  cJSON_GetArraySize(json);
    memset(rand_seed, -1, sizeof(rand_seed));
    // head = (struct node *)malloc(sizeof(struct node));
    // end = (struct node *)malloc(sizeof(struct node)); 
    // end = head;

    f=fopen("./output","r");
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


    char* string = "1231231asdasdasdasdasdasdaskjdlahslkdhsakfhlksajdhfkjasldhfkjlasdhfkjashdfkjhasdasdfasdf23123";
    char* strtem = (char*)malloc(strlen(string));
    strcpy(strtem, string);
    char* origin = (char*)malloc(strlen(string));
    strcpy(origin, string);
    // json_init_key(json);

    for (int i = 0; i < cJSON_GetArraySize(json); ++i)
    {

      cJSON * item = cJSON_GetArrayItem(json, i); 
      if (rand_seed[i/10] == -1)
        rand_seed[i/10] = rand()%1024; 
      int _pos = (i%10)+1;
      //cannot access
      if ((rand_seed[i/10] >> _pos) < 0)
        continue;
      //can replace
      if(rand_seed[i/10] & _pos)
      {
        for (int j = 0; j < cJSON_GetArraySize(item); ++j)
        {
          cJSON * child = cJSON_GetArrayItem(item, j); 
          char* _val = cJSON_Print(child);
          char val = (char)atoi(_val);
          if (strtem[atoi(child->string)] != origin[atoi(child->string)])
            continue;
          if (val == 0) val = 27;  
          strtem[atoi(child->string)] = val; 
        } 
      }
    } 
    string = strtem;
    puts(string); 
    return 0;
}
