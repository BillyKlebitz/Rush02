#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_list
{
	char 	*key;
	char 	*value;
	struct s_list *next;
}				t_list;

t_list *create_list(char *key, char *value)
{
	t_list *item;
	
	item = (t_list *)malloc(sizeof(t_list));
	item->key = key;
	item->value = value;
	item->next = NULL;
	return (item);
}

int str_len(char *str)
{
	int i;
	
	i = 0;
	while (str[i] != '\n')
		i++;
	return (i);
}

t_list *edit_str(char *str)
{
	char *key;
	char *value;
	int i;
	int j;
	
	i = 0;
	j = 0;
	key = (char *)malloc(sizeof(char) * 1000);
	value = (char *)malloc(sizeof(char) * 1000);
	while (str[i] != ':')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	i += 2;
	while (str[i] != '\n')
	{
		value[j] = str[i];
		i++;
		j++;
	}
	value[j] = '\0';
	//printf("%s\n", key);
	//printf("%s\n", value);
	
	return (create_list(key, value));
	
//	free(key);
//	free(value);
}

void clean_str(char *str)
{
	int i;
	
	i = 0;
	while(str[i])
	{
		str[i] = 0;
		i++;
	}
}

void print_list(t_list *p)
{
	printf("key=%s  value=%s\n", p->key, p->value);
	if(p->next != NULL)
		print_list(p->next);
}

int main(int argc, char **argv)
{
	int fd;
	char buffer[4096];
	char str[100];
	int size;
	int i;
	int j;

	t_list *node = NULL;
	t_list *begin;
	
	//begin = node;
	(void)argv;
	i = 0;
	j = 0;
	if (argc == 1)
	{
		fd = open("numbers.dict", O_RDONLY);
		size = read(fd,buffer,4096);
		i = 0;
		while (buffer[i] != '\0')
		{
			j = 0;
			while (buffer[i] != '\n' && buffer[i] != '\0')
			{
				str[j] = buffer[i];
				j++;
				i++;
			}
			str[i+1] = '\0';
			i++;
			if(node == NULL)
			{
				node = edit_str(str);
				begin = node;
			}
			else
			{	
			node->next = edit_str(str);
			node = node->next;
			}
			clean_str(str);
		}	
		print_list(begin);
	}
	return (0);
}
