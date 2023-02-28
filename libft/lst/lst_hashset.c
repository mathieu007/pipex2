/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_hashset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:32:49 by mroy              #+#    #+#             */
/*   Updated: 2023/02/24 13:32:52 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #define CAPACITY 50000 // Size of the Hash Table

// unsigned long	hash_function(char *str)
// {
// 	unsigned long	i;

// 	i = 0;
// 	for (int j = 0; str[j]; j++)
// 		i += str[j];
// 	return (i % CAPACITY);
// }

// typedef struct Ht_item		Ht_item;

// // Define the Hash Table Item here
// struct						Ht_item
// {
// 	char					*key;
// 	char					*value;
// };

// typedef struct LinkedList	LinkedList;

// // Define the Linkedlist here
// struct						LinkedList
// {
// 	Ht_item					*item;
// 	LinkedList				*next;
// };

// typedef struct HashTable	HashTable;

// // Define the Hash Table here
// struct						HashTable
// {
// 	// Contains an array of pointers
// 	// to items
// 	Ht_item					**items;
// 	LinkedList				**overflow_buckets;
// 	int						size;
// 	int						count;
// };

// static LinkedList	*allocate_list(void)
// {
// 	LinkedList	*list;

// 	// Allocates memory for a Linkedlist pointer
// 	list = (LinkedList *)malloc(sizeof(LinkedList));
// 	return (list);
// }

// static LinkedList	*linkedlist_insert(LinkedList *list, Ht_item *item)
// {
// 	LinkedList	*head;
// 	LinkedList	*node;
// 	LinkedList	*temp;
// 	LinkedList	*node;

// 	// Inserts the item onto the Linked List
// 	if (!list)
// 	{
// 		head = allocate_list();
// 		head->item = item;
// 		head->next = NULL;
// 		list = head;
// 		return (list);
// 	}
// 	else if (list->next == NULL)
// 	{
// 		node = allocate_list();
// 		node->item = item;
// 		node->next = NULL;
// 		list->next = node;
// 		return (list);
// 	}
// 	temp = list;
// 	while (temp->next->next)
// 	{
// 		temp = temp->next;
// 	}
// 	node = allocate_list();
// 	node->item = item;
// 	node->next = NULL;
// 	temp->next = node;
// 	return (list);
// }

// static Ht_item	*linkedlist_remove(LinkedList *list)
// {
// 	LinkedList	*node;
// 	LinkedList	*temp;
// 	Ht_item		*it;

// 	// Removes the head from the linked list
// 	// and returns the item of the popped element
// 	if (!list)
// 		return (NULL);
// 	if (!list->next)
// 		return (NULL);
// 	node = list->next;
// 	temp = list;
// 	temp->next = NULL;
// 	list = node;
// 	it = NULL;
// 	memcpy(temp->item, it, sizeof(Ht_item));
// 	free(temp->item->key);
// 	free(temp->item->value);
// 	free(temp->item);
// 	free(temp);
// 	return (it);
// }

// static void	free_linkedlist(LinkedList *list)
// {
// 	LinkedList	*temp;

// 	temp = list;
// 	while (list)
// 	{
// 		temp = list;
// 		list = list->next;
// 		free(temp->item->key);
// 		free(temp->item->value);
// 		free(temp->item);
// 		free(temp);
// 	}
// }

// static LinkedList	**create_overflow_buckets(HashTable *table)
// {
// 	LinkedList	**buckets;

// 	// Create the overflow buckets; an array of linkedlists
// 	buckets = (LinkedList **)calloc(table->size, sizeof(LinkedList *));
// 	for (int i = 0; i < table->size; i++)
// 		buckets[i] = NULL;
// 	return (buckets);
// }

// static void	free_overflow_buckets(HashTable *table)
// {
// 	LinkedList	**buckets;

// 	// Free all the overflow bucket lists
// 	buckets = table->overflow_buckets;
// 	for (int i = 0; i < table->size; i++)
// 		free_linkedlist(buckets[i]);
// 	free(buckets);
// }

// Ht_item	*create_item(char *key, char *value)
// {
// 	Ht_item	*item;

// 	// Creates a pointer to a new hash table item
// 	item = (Ht_item *)malloc(sizeof(Ht_item));
// 	item->key = (char *)malloc(strlen(key) + 1);
// 	item->value = (char *)malloc(strlen(value) + 1);
// 	strcpy(item->key, key);
// 	strcpy(item->value, value);
// 	return (item);
// }

// HashTable	*create_table(int size)
// {
// 	HashTable	*table;

// 	// Creates a new HashTable
// 	table = (HashTable *)malloc(sizeof(HashTable));
// 	table->size = size;
// 	table->count = 0;
// 	table->items = (Ht_item **)calloc(table->size, sizeof(Ht_item *));
// 	for (int i = 0; i < table->size; i++)
// 		table->items[i] = NULL;
// 	table->overflow_buckets = create_overflow_buckets(table);
// 	return (table);
// }

// void	free_item(Ht_item *item)
// {
// 	// Frees an item
// 	free(item->key);
// 	free(item->value);
// 	free(item);
// }

// void	free_table(HashTable *table)
// {
// 	Ht_item	*item;

// 	// Frees the table
// 	for (int i = 0; i < table->size; i++)
// 	{
// 		item = table->items[i];
// 		if (item != NULL)
// 			free_item(item);
// 	}
// 	free_overflow_buckets(table);
// 	free(table->items);
// 	free(table);
// }

// void	handle_collision(HashTable *table, unsigned long index, Ht_item *item)
// {
// 	LinkedList	*head;

// 	head = table->overflow_buckets[index];
// 	if (head == NULL)
// 	{
// 		// We need to create the list
// 		head = allocate_list();
// 		head->item = item;
// 		table->overflow_buckets[index] = head;
// 		return ;
// 	}
// 	else
// 	{
// 		// Insert to the list
// 		table->overflow_buckets[index] = linkedlist_insert(head, item);
// 		return ;
// 	}
// }

// void	ht_insert(HashTable *table, char *key, char *value)
// {
// 	Ht_item			*item;
// 	unsigned long	index;
// 	Ht_item			*current_item;

// 	// Create the item
// 	item = create_item(key, value);
// 	// Compute the index
// 	index = hash_function(key);
// 	current_item = table->items[index];
// 	if (current_item == NULL)
// 	{
// 		// Key does not exist.
// 		if (table->count == table->size)
// 		{
// 			// Hash Table Full
// 			printf("Insert Error: Hash Table is full\n");
// 			// Remove the create item
// 			free_item(item);
// 			return ;
// 		}
// 		// Insert directly
// 		table->items[index] = item;
// 		table->count++;
// 	}
// 	else
// 	{
// 		// Scenario 1: We only need to update value
// 		if (strcmp(current_item->key, key) == 0)
// 		{
// 			strcpy(table->items[index]->value, value);
// 			return ;
// 		}
// 		else
// 		{
// 			// Scenario 2: Collision
// 			handle_collision(table, index, item);
// 			return ;
// 		}
// 	}
// }

// char	*ht_search(HashTable *table, char *key)
// {
// 	int			index;
// 	Ht_item		*item;
// 	LinkedList	*head;

// 	// Searches the key in the hashtable
// 	// and returns NULL if it doesn't exist
// 	index = hash_function(key);
// 	item = table->items[index];
// 	head = table->overflow_buckets[index];
// 	// Ensure that we move to items which are not NULL
// 	while (item != NULL)
// 	{
// 		if (strcmp(item->key, key) == 0)
// 			return (item->value);
// 		if (head == NULL)
// 			return (NULL);
// 		item = head->item;
// 		head = head->next;
// 	}
// 	return (NULL);
// }

// void	print_search(HashTable *table, char *key)
// {
// 	char	*val;

// 	if ((val = ht_search(table, key)) == NULL)
// 	{
// 		printf("%s does not exist\n", key);
// 		return ;
// 	}
// 	else
// 	{
// 		printf("Key:%s, Value:%s\n", key, val);
// 	}
// }

// void	print_table(HashTable *table)
// {
// 	LinkedList	*head;

// 	printf("\n-------------------\n");
// 	for (int i = 0; i < table->size; i++)
// 	{
// 		if (table->items[i])
// 		{
// 			printf("Index:%d, Key:%s, Value:%s", i, table->items[i]->key,
// 					table->items[i]->value);
// 			if (table->overflow_buckets[i])
// 			{
// 				printf(" => Overflow Bucket => ");
// 				head = table->overflow_buckets[i];
// 				while (head)
// 				{
// 					printf("Key:%s, Value:%s ", head->item->key,
// 							head->item->value);
// 					head = head->next;
// 				}
// 			}
// 			printf("\n");
// 		}
// 	}
// 	printf("-------------------\n");
// }

// // int	main(void)
// // {
// // 	HashTable *ht = create_table(CAPACITY);
// // 	ht_insert(ht, "1", "First address");
// // 	ht_insert(ht, "2", "Second address");
// // 	ht_insert(ht, "Hel", "Third address");
// // 	ht_insert(ht, "Cau", "Fourth address");
// // 	print_search(ht, "1");
// // 	print_search(ht, "2");
// // 	print_search(ht, "3");
// // 	print_search(ht, "Hel");
// // 	print_search(ht, "Cau");
// // 	print_table(ht);
// // 	free_table(ht);
// // 	return (0);
// // }