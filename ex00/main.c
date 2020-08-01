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

int	ft_strlen(char *str)
{
	const char *a = str;

	while (*str)
		++str;
	return (str - a);
}

int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			return (unsigned char *)s1 - (unsigned char *)s2;
		}
		s1++;
		s2++;	
	}
	return (0);
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
	while (str[i] >= '0' && str[i] <= '9')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	i++;
	while (str[i] != '\n')
	{	
		while (str[i] == ' ' || str[i] == ':')
			i++;
		value[j] = str[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (create_list(key, value));
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

void result(char *argv, t_list *begin)
{
	t_list *node = begin;
	while(node)
	{
		if(


		if(ft_strlen(argv) == ft_strlen(node->key) && ft_strlen(node->key) > 2)
		{
			result(argv[0], begin);
			write(1,node->value, ft_strlen(node->value));
			argv++;
			result(argv, begin);
			//return ;
		}
		else
			node = node->next;
	}

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
	
	i = 0;
	j = 0;
	if (argc > 0 )
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
			str[j] = '\0';
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
		//print_list(begin);
		result(argv[1], begin);
	}
	return (0);
}
