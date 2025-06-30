/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:01:32 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 22:42:09 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

/*
Part 1 - Libc functions (MANDATORY)
*/

// Checks for an alphabetic character. It returns true if c is an uppercase
// or lowercase letter, and false otherwise.
int		ft_isalpha(int c);

// Checks for a digit (0-9). It returns true if c is a digit, and false
// otherwise.
int		ft_isdigit(int c);

// Checks for an alphanumeric character. It returns true if c is an alphabetic
// or numeric character, and false otherwise.
int		ft_isalnum(int c);

// Checks if c is a 7-bit unsigned char value that fits into the ASCII character
// set.
int		ft_isascii(int c);

// Checks for any printable character including space (' ').
int		ft_isprint(int c);

// Calculates the length of the string s, excluding the terminating null byte
// ('\0').
size_t	ft_strlen(const char *s);

// Fills the first len bytes of the memory area pointed to by b with the
// constant byte c.
void	*ft_memset(void *b, int c, size_t len);

// Writes n zero-valued bytes to the string s. If n is zero, ft_bzero() does
// nothing.
void	ft_bzero(void *s, size_t n);

// Copies n bytes from memory area src to memory area dst. The memory areas must
// not overlap. Use ft_memmove() if overlapping areas are possible.
void	*ft_memcpy(void *dst, const void *src, size_t n);

// Copies len bytes from memory area src to memory area dst. Memory areas 
// overlap: copying always takes place as if the bytes in src are first copied
// into a temporary array that does not overlap either src or dst, and then the
// bytes are copied from the temporary array to dst.
void	*ft_memmove(void *dst, const void *src, size_t len);

// Copies up to size - 1 bytes from the null-terminated string src to dst,
// null-terminating the result. The result will be null-terminated if size
// is > 0.
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

// Appends the null-terminated string src to the end of dst. It will append at
// most size - strlen(dst) - 1 bytes, null-terminating the result. The size
// argument should be the full size of the destination buffer.
size_t	ft_strlcat(char *dst, const char *src, size_t size);

// Converts a lowercase letter to the corresponding uppercase letter. If the
// argument is not a lowercase letter, it is returned unchanged.
int		ft_toupper(int c);

// Converts an uppercase letter to the corresponding lowercase letter. If the
// argument is not an uppercase letter, it is returned unchanged.
int		ft_tolower(int c);

// Locates the first occurrence of c (converted to a char) in the string pointed
// to by s. The terminating null byte is considered part of the string.
char	*ft_strchr(const char *s, int c);

// Locates the last occurrence of c (converted to a char) in the string pointed
// to by s. The terminating null byte is considered part of the string.
char	*ft_strrchr(const char *s, int c);

// Lexicographically compares the first n bytes of the null-terminated strings
// s1 and s2.
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// Locates the first occurrence of c (converted to an unsigned char) in the
// first n bytes of the string s.
void	*ft_memchr(const void *s, int c, size_t n);

// Compares the first n bytes (each interpreted as unsigned char) of the
// memory areas s1 and s2.
int		ft_memcmp(const void *s1, const void *s2, size_t n);

// Locates the first occurrence of the null-terminated string needle in the
// string haystack, where not more than len characters are searched. Characters
// after a '\0' are not searched.
char	*ft_strnstr(const char *haystack, const char *needle,
			size_t len);

// Converts the initial portion of the string pointed to by str to an integer.
int		ft_atoi(const char *str);

// Allocates contiguous memory for an array of count elements of size bytes,
// each, and initializes the memory to zero. Returns a pointer to the allocated
// memory.
void	*ft_calloc(size_t count, size_t size);

// Allocates sufficient memory for a copy of the string s1, does the copy, and
// returns a pointer to the new string. The caller should free the allocated
// memory.
char	*ft_strdup(const char *s1);

/*
Part 2 - Additional functions (Mandatory)
*/

// Allocates memory (using malloc(3)) and returns a
// substring from the string 's'.
// The substring starts at index 'start' and has a
// maximum length of 'len'.
char	*ft_substr(char const *s, unsigned int start, size_t len);

// Allocates memory (using malloc(3)) and returns a
// new string, which is the result of concatenating
// 's1' and 's2'.
char	*ft_strjoin(char const *s1, char const *s2);

// Allocates memory (using malloc(3)) and returns a
// copy of ’s1’ with characters from ’set’ removed
// from the beginning and the end.
char	*ft_strtrim(char const *s1, char const *set);

// Allocates memory (using malloc(3)) and returns an
// array of strings obtained by splitting ’s’ using
// the character ’c’ as a delimiter. The array must
// end with a NULL pointer.
char	**ft_split(char const *s, char c);

// Allocates memory (using malloc(3)) and returns
// a string representing the integer received as an
// argument. Negative numbers must be handled.
char	*ft_itoa(int n);

// Applies the function f to each character of the
// string s, passing its index as the first argument
// and the character itself as the second. A new
// string is created (using malloc(3)) to store the
// results from the successive applications of f.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

// Applies the function ’f’ to each character of the
// string passed as argument, passing its index as
// the first argument. Each character is passed by
// address to ’f’ so it can be modified if necessary.
void	ft_striteri(char *s, void (*f)(unsigned int,
				char*));

// Outputs the character ’c’ to the specified file
// descriptor.
void	ft_putchar_fd(char c, int fd);

// Outputs the string ’s’ to the specified file
// descriptor.
void	ft_putstr_fd(char *s, int fd);

// Outputs the string ’s’ to the specified file
// descriptor followed by a newline.
void	ft_putendl_fd(char *s, int fd);

// Outputs the integer ’n’ to the specified file
// descriptor.
void	ft_putnbr_fd(int n, int fd);

/*
Bonus Part
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

// Allocates memory (using malloc(3)) and returns
// a new node. The ’content’ member variable is
// initialized with the given parameter ’content’.
// The variable ’next’ is initialized to NULL.
t_list	*ft_lstnew(void *content);

// lst: The address of a pointer to the first node of
// a list.
// new: The address of a pointer to the node to be
// added.
void	ft_lstadd_front(t_list **lst, t_list *new);

// Counts the number of nodes in the list.
int		ft_lstsize(t_list *lst);

// Returns the last node of the list.
t_list	*ft_lstlast(t_list *lst);

// Adds the node ’new’ at the end of the list.
void	ft_lstadd_back(t_list **lst, t_list *new);

// Takes a node as parameter and frees its content
// using the function ’del’. Free the node itself but
// does NOT free the next node.
void	ft_lstdelone(t_list *lst, void (*del)(void*));

// Deletes and frees the given node and all its
// successors, using the function ’del’ and free(3).
// Finally, set the pointer to the list to NULL.
void	ft_lstclear(t_list **lst, void (*del)(void*));

// Iterates through the list ’lst’ and applies the
// function ’f’ to the content of each node.
void	ft_lstiter(t_list *lst, void (*f)(void*));

// Iterates through the list ’lst’, applies the
// function ’f’ to each node’s content, and creates
// a new list resulting of the successive applications
// of the function ’f’. The ’del’ function is used to
// delete the content of a node if needed.
t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *));

/*
Legacy Garbage
*/
// void			*ft_memccpy(void *dst, const void *src, int c, size_t n);

#endif