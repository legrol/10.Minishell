/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:01:14 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/14 19:56:06 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_split_and_update_tokens" combines the process of splitting 
 * a token and updating the types of tokens in the linked list.
 * 
 * @param t_token *token		A pointer to the token to be processed. This 
 *								function updates the list by splitting the 
 *								token and adjusting their types.
 * 
 * The function "ft_split_tokens" splits the value of the given token by a 
 * delimiter (e.g., '|') and creates a linked list of new tokens for each 
 * part. It modifies the original token and adds new tokens as needed.
 * 
 * @param t_token *token		A pointer to the token to be split.
 * @return t_token*				A pointer to the last token created in the 
 *								list or NULL if memory allocation fails.
 *
 * The function "ft_create_new_token" creates a new token, sets its value, 
 * links it to the previous token, and returns the newly created token.
 * 
 * @param t_token *current		A pointer to the current token, which will be 
 *								linked to the new token.
 * @param char *value			A string containing the value for the new token.
 * @return t_token*				A pointer to the newly created token, or NULL 
 *								if memory allocation fails.
 * 
 * The function "ft_update_tokens" iterates through a linked list of tokens
 * and updates their types based on their values and positions.
 * 
 * @param t_token *token		A pointer to the starting token in the 
 *								linked list. Each token's type will be updated.
 * 
 */

static void	ft_update_tokens(t_token *token)
{
	while (token)
	{
		ft_update_type_tokens(token);
		token = token->next;
	}
}

static t_token	*ft_create_new_token(t_token *current, char *value)
{
	// // current->next = malloc(sizeof(t_token));
	// // if (!current->next)
	// // 	return (NULL);
	// // current->next->prev = current;
	// // current = current->next;
	// // current->token_value = strdup(value);
	// // current->next = NULL;
	// // return (current);

	// t_token *new_token = malloc(sizeof(t_token));
    // if (!new_token)
    //     return NULL;

    // new_token->prev = current;
    // new_token->token_value = strdup(value);
    // new_token->next = NULL;

    // current->next = new_token;
    // return new_token;

	t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;

    new_token->prev = current;
    new_token->token_value = strdup(value);  // Duplica el valor del token
    if (!new_token->token_value)             // Comprueba que strdup no falle
    {
        free(new_token);
        return NULL;
    }
    new_token->next = NULL;

    current->next = new_token;
    return new_token;

}

//INICIAL
// static t_token	*ft_split_tokens(t_token *token)
// {
// 	int		i;
// 	char	**sub_tokens;
// 	t_token	*current;

// 	char	*test;
// 	char	*test2;

// 	sub_tokens = NULL;
// 	// if (!ft_strchr(token->token_value, '|'))
// 	// 	return (token);
// 	// sub_tokens = ft_split(token->token_value, '|');
// 	// if (!sub_tokens)
// 	// 	return (token);

// 	ft_printf("Estoy en split_tokens\n");
// 	ft_printf("token_value = %s\n", token->token_value);
// 	if ((!ft_strchr(token->token_value, '|')) && (!ft_strchr(token->token_value, '-')))
// 	{
// 		test = ft_strchr(token->token_value, '-');
// 		test2 = ft_strchr(token->token_value, '|');
// 		ft_printf("token_value = %s\n", token->token_value);
// 		ft_printf("test = %s\n", test);
// 		ft_printf("test2 = %s\n", test2);
// 		ft_printf("Estoy en splittokens_no\n\n");
// 		return (token);
// 	}

// 	if (ft_strchr(token->token_value, '|'))
// 	{
// 		ft_printf("Estoy en pipe\n");
// 		sub_tokens = ft_split(token->token_value, '|');
// 	}
// 	// else if (ft_strchr(token->token_value, '-'))
// 	// {
// 	// 	ft_printf("Estoy en guion\n");
// 	// 	sub_tokens = ft_split_minus(token->token_value, '-');	
// 	// }
// 	if (!sub_tokens)
// 		return (token);
// 	current = token;
// 	i = 0;
// 	while (sub_tokens[i])
// 	{
// 		free(current->token_value);
// 		current->token_value = strdup(sub_tokens[i++]);
// 		if (!current->token_value)
// 			return (ft_free_split(sub_tokens), NULL);
// 		if (sub_tokens[i])
// 		{
// 			current = ft_create_new_token(current, sub_tokens[i]);
// 			if (!current)
// 				return (ft_free_split(sub_tokens), NULL);
// 		}
// 	}
// 	return (ft_free_split(sub_tokens), token);
// }

//SEGUNDO
// static t_token *ft_split_tokens(t_token *token)
// {
//     int i;
//     char **pipe_tokens;
//     char **sub_tokens;
//     t_token *current = token;

// 	char	*test;
// 	char	*test2;

// 	sub_tokens = NULL;
// 	pipe_tokens = NULL;
// 	current = token;

// 	ft_printf("Estoy en split_tokens\n");
// 	ft_printf("token_value = %s\n", token->token_value);
//     if (!ft_strchr(token->token_value, '|') && !ft_strchr(token->token_value, '-'))
//     {
// 		// test = ft_strchr(token->token_value, '-');
// 		// test2 = ft_strchr(token->token_value, '|');
// 		// ft_printf("token_value = %s\n", token->token_value);
// 		// ft_printf("test = %s\n", test);
// 		// ft_printf("test2 = %s\n", test2);
// 		// ft_printf("Estoy en splittokens_no\n\n");
// 		return token;
// 	}

//     // Primero, dividimos por el delimitador '|'
//     if (ft_strchr(token->token_value, '|'))
//         pipe_tokens = ft_split(token->token_value, '|');
//     else
// 	{
//         ft_printf("Estoy en gestion sin pipe\n");
// 		pipe_tokens = malloc(sizeof(char *) * 2); // Para el caso sin '|'
//         pipe_tokens[0] = strdup(token->token_value);
// 		ft_printf("%s\n", pipe_tokens[0]);
//         pipe_tokens[1] = NULL;
// 		ft_printf("%s\n", pipe_tokens[1]);
// 	}

//     i = 0;
//     while (pipe_tokens[i])
//     {
//         ft_printf("Entro en pipe tokens\n");
// 		sub_tokens = ft_split_minus(pipe_tokens[i], '-'); // Separar cada token por '-'
//         int j = 0;
//         while (sub_tokens[j])
//         {
//             ft_printf("entro en subtokens\n");
// 			free(current->token_value);
//             current->token_value = strdup(sub_tokens[j++]); // Actualiza el token actual
//             if (!current->token_value)
//                 return (ft_free_split(pipe_tokens), ft_free_split(sub_tokens), NULL);

//             if (sub_tokens[j])
//                 current = ft_create_new_token(current, sub_tokens[j]); // Crear nuevo token si hay más
//         }
//         ft_free_split(sub_tokens);
//         i++;
//         if (pipe_tokens[i])
//             current = ft_create_new_token(current, pipe_tokens[i]);
//     }
// 	// ft_printf("xxx\n");
//     // ft_free_split(pipe_tokens);
//     return (ft_free_split(pipe_tokens), token);
// }

//TERCERO
// static t_token *ft_split_tokens(t_token *token)
// {
// 	char **sub_tokens;
// 	t_token *current = token;

// 	ft_printf("Estoy en split_tokens\n");
// 	ft_printf("token = %s\n", current->token_value);
// 	ft_printf("token_value = %s\n", token->token_value);

// 	// Aplica ft_split_minus para separar el token en "ls" y "-l" si contiene '-'
// 	if (ft_strchr(token->token_value, '-'))
// 	{
// 		sub_tokens = ft_split_minus(token->token_value, '-'); // Separar cada token por '-'

// 		int i = 0;

// 		while (sub_tokens[i])
// 		{
// 			ft_printf("\nsub_token = %s i = %i\n", sub_tokens[i], i);
// 			if (i == 0)  // Para el primer token, actualiza el valor del token actual
// 			{
// 				ft_printf("Entro en i = 0\n");
// 				free(current->token_value);
// 				current->token_value = strdup(sub_tokens[i]);
// 				ft_printf("index = %i current_token = %s\n", i, current->token_value);			
// 				if (!current->token_value)
// 					return (ft_free_split(sub_tokens), NULL);
// 			}
// 			else  // Para tokens adicionales, crea un nuevo nodo en la lista
// 			{
// 				ft_printf("Entro en else secundario\n");
// 				current = ft_create_new_token(current, sub_tokens[i]);				
// 				if (!current)
// 					return (ft_free_split(sub_tokens), NULL);
// 				// current->token_value = strdup(sub_tokens[i]); // Asigna el valor al nuevo nodo
// 				ft_printf("current_token_value = %s\n", current->token_value);
// 				// if (!current->token_value)
// 				// 	return (ft_free_split(sub_tokens), NULL);
// 			}
// 			i++;
// 		}
		
// 		ft_free_split(sub_tokens); // Liberamos sub_tokens después de procesarlos
// 	}
// 	else
// 	{
// 		// Si no hay '-', simplemente mantenemos el token original
// 		ft_printf("Entro en else principal\n");
// 		current->token_value = strdup(token->token_value);
// 		ft_printf("current_token_value = %s\n\n", current->token_value);
// 	}
// 	ft_printf("1.current_token_value = %s\n\n", current->token_value);
// 	//ft_printf("2.current_next_token_value = %s\n", current->next->token_value);
// 	// return token;
// 	return (token);
// }

//CUARTO
// static t_token *ft_split_tokens(t_token *token)
// {
//     char **sub_tokens;
//     t_token *current = token;

//     ft_printf("Estoy en split_tokens\n");
//     ft_printf("token = %s\n", current->token_value);
// 	ft_printf("token_value = %s\n", token->token_value);
	
//     // Aplica ft_split_minus para separar el token en "ls" y "-l" si contiene '-'
//     if (ft_strchr(token->token_value, '-'))
//     {
//         sub_tokens = ft_split_minus(token->token_value, '-'); // Separar cada token por '-'

//         int i = 0;
//         while (sub_tokens[i])
//         {
//             ft_printf("\nsub_token = %s i = %i\n", sub_tokens[i], i);
            
//             if (i == 0)  // Para el primer sub-token, actualiza el valor del token actual
//             {
//                 free(current->token_value);  // Liberamos el valor anterior de `token_value`
//                 current->token_value = strdup(sub_tokens[i]);
//                 if (!current->token_value)
//                     return (ft_free_split(sub_tokens), NULL);
//                 ft_printf("index = %i current_token_value = %s\n", i, current->token_value);
//             }
//             else  // Para sub-tokens adicionales, crea un nuevo nodo
//             {
//                 ft_printf("Entro en else secundario\n");
// 				current = ft_create_new_token(current, sub_tokens[i]);
//                 if (!current)
//                     return (ft_free_split(sub_tokens), NULL);
//                 ft_printf("new_node_token_value = %s\n", current->token_value);
//             }
//             i++;
//         }

//         ft_free_split(sub_tokens); // Liberamos `sub_tokens` después de procesarlos
//     }
//     else
//     {
//         // Si no hay '-', mantenemos el token original
//         ft_printf("Entro en else principal\n");
// 		current->token_value = strdup(token->token_value);
//         if (!current->token_value)
//             return NULL;
//         ft_printf("single_token_value = %s\n", current->token_value);
//     }
// 	ft_printf("1.current_token_value = %s\n\n", current->token_value);

// 	// Depuración: Recorre y muestra toda la lista enlazada de tokens
//     t_token *temp = token;
//     ft_printf("\nRecorriendo lista de tokens:\n");
//     while (temp)
//     {
//         ft_printf("Token en lista: %s\n", temp->token_value);
//         temp = temp->next;
//     }

//     return token;
// }

//QUINTO
static t_token *ft_split_tokens(t_token *token)
{
    char **sub_tokens;
    t_token *current = token;
    t_token *last_node = current;

	ft_printf("Estoy en split_tokens\n");
	ft_printf("token = %s\n", current->token_value);
	ft_printf("token_value = %s\n\n", token->token_value);

    //Aplica ft_split_minus para separar el token en "ls" y "-l" si contiene '-'
    if (ft_strchr(token->token_value, '-'))
    {
        sub_tokens = ft_split_minus(token->token_value, '-'); // Separar cada token por '-'

        int i = 0;
        
        // Procesar cada sub_token y añadirlo como un nuevo nodo si es necesario
        while (sub_tokens[i])
        {
            ft_printf("\nsub_token = %s i = %i\n", sub_tokens[i], i);
			if (i == 0)  // Para el primer sub-token, actualiza el valor del token actual
            {
                free(current->token_value);
                current->token_value = strdup(sub_tokens[i]);
                if (!current->token_value)
                    return (ft_free_split(sub_tokens), NULL);
				ft_printf("index = %i current_token_value = %s\n", i, current->token_value);
            }
            else  // Para sub-tokens adicionales, crea y enlaza un nuevo nodo
            {
                ft_printf("Entro en else secundario\n");
				last_node = ft_create_new_token(last_node, sub_tokens[i]);
                if (!last_node)
                    return (ft_free_split(sub_tokens), NULL);
				ft_printf("new_node_token_value = %s\n", last_node->token_value);
            }
            i++;
        }

        ft_free_split(sub_tokens); // Liberamos `sub_tokens` después de procesarlos
    }
	else
    {
        // Si no hay '-', mantenemos el token original
        ft_printf("Entro en else principal\n");
		current->token_value = strdup(token->token_value);
        if (!current->token_value)
            return NULL;
        ft_printf("single_token_value = %s\n", current->token_value);
    }

    return last_node; // Retorna el último nodo de la lista
}



//PRIMERA
// void	ft_split_and_update_tokens(t_token *token)
// {
// 	t_token	*last_token;

// 	last_token = ft_split_tokens(token);
// 	ft_update_tokens(last_token);
// 	//ft_update_tokens(token);
// }

//SEGUNDA
// void ft_split_and_update_tokens(t_token *token)
// {
//     t_token *current = token;
//     t_token *last_token = token;

//     while (current)
//     {
//         last_token = ft_split_tokens(current); // Procesa cada token y añade sub-tokens si es necesario
//         if (!last_token)
//             return; // Manejo de error si alguna tokenización falla

//         current = last_token->next; // Avanza al siguiente token en la lista si existe
//     }

//     // Actualizar los tipos de todos los tokens en la lista completa
//     ft_update_tokens(token);
// }

//TERCERA
void ft_split_and_update_tokens(t_token *token)
{
    t_token *current = token;
    t_token *last_token = NULL;

    while (current)
    {
        last_token = ft_split_tokens(current); // Procesa cada token y conecta sub-tokens
        if (!last_token)
            return; // Salir si hay un fallo de tokenización

        // Depuración: Mostrar el último token procesado
        ft_printf("Último token después de split_tokens: %s\n", last_token->token_value);

        // Si el último token tiene un siguiente, avanzamos; si no, conectamos el próximo `current`
        if (last_token->next == NULL)
            current = current->next;
        else
            current = last_token->next;
    }

    // Recorre y muestra toda la lista de tokens para verificar el enlace correcto
    t_token *temp = token;
    ft_printf("\nLista de tokens final:\n");
    while (temp)
    {
        ft_printf("Token en lista: %s\n", temp->token_value);
        temp = temp->next;
    }

    // Actualización de los tipos de tokens en la lista
    ft_update_tokens(token);
}
