//
// EECS2031 team.c
//
// This is a program for creating a football team programmed in C.
//
//
// My Program uses a linked list data structure for storing the players.
//
// Author: Sami Tarazi
// Student Info: 214487847


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

//**********************************************************************

struct player {
  char * familyName;
  char * firstName;
  char position;
  int value;
};

struct node {
  struct player playerInfo;
  int value;
  struct node * next;
};


//**********************************************************************
// my functions
struct node* add_node(struct node*, struct node*, struct player*);
struct node * searchByFamily(struct node *head, char familyName[]);
void searchByValue(struct node *head, int value);
void print_player(struct node *searched_node);
struct node * delete_node(struct node * head, char familyName[]);
void delete_all_team(struct node*);
void deletePlayer(struct player*);
void freeNode(struct node *node_to_delete);
void print_all_team(struct node *head);
void updateHeadAndTail(struct node *tmpNode, struct node *head, struct node* current);
void addStringToPlayer(struct player *, char *, char[]);

// - - - - - - - - - - - - - - - - - - - - -
void safegets (char s[], int arraySize);        // gets without buffer overflow
void familyNameDuplicate (char familyName[]);   // marker/tester friendly
void familyNameFound (char familyName[]);       //   functions to print
void familyNameNotFound (char familyName[]);    //     messages to user
void familyNameDeleted (char familyName[]);
void printTeamEmpty (void);
void printTeamTitle(void);
void printNoPlayersWithLowerValue(int value);

//**********************************************************************
// Program-wide Constants
//

const int MAX_LENGTH = 1023;
const char NULL_CHAR = '\0';
const char NEWLINE = '\n';
const char GOALKEEPER = 'G';
const char DEFENDER = 'D';
const char MIDFIELDER = 'M';
const char STRIKER = 'S';



//**********************************************************************
// Main Program
//

int main (void)
{
    const char bannerString[]
        = "\nPersonal Team Maintenance Program.\n\n";
    const char commandList[]
        = "Commands are I (insert), D (delete), S (search by name),\n"
          "  V (search by value), P (print), Q (quit).\n";

    struct node *head = NULL, *current = NULL; // define a head and a tail (current) that will keep track of first and last node
    struct player * playerInfo = malloc(sizeof(struct player)); // define player struct

    //printing simple lines
    printf("%s",bannerString);
    printf("%s",commandList);

    char response;
    char input[MAX_LENGTH+1];
    char *userInput;

    do

    {
        printf("\nCommand?: ");
        safegets(input,MAX_LENGTH+1);
        response = toupper(input[0]);

        if (strlen(input) > 1)
          printf("\nInvalid command.\n%s\n",commandList);

        else

        if (response == 'I')
        {
          //--------------- A. Family and First Name ---------------

          printf("Family Name: ");
          safegets(input, MAX_LENGTH+1);
          userInput = &input[0];
          addStringToPlayer(playerInfo, userInput, "Family"); // add family name to struct

          printf("First Name: ");
          safegets(input, MAX_LENGTH+1);
          userInput = &input[0];
          addStringToPlayer(playerInfo, userInput, "First"); // add first name to struct

          // --------------- B. Position ---------------
          printf("Position: ");
          safegets(input, MAX_LENGTH+1);
          playerInfo->position = toupper(input[0]);


          // --------------- C. VALUE ---------------
          printf("Value: ");
          safegets(input, MAX_LENGTH+1);
          playerInfo->value = atoi(input);



          if (head != NULL) { // if list is non-empty
            struct node * tmpNode = add_node(head, current, playerInfo); // adds node and returns it in temporary variable
//            updateHeadAndTail(&tmpNode, &head, &current); // update head and current nodes

            if (tmpNode->next != NULL // check if node is added in the beginning
                && (strcmp(head->playerInfo.familyName, tmpNode->next->playerInfo.familyName) == 0)
               )
            {
              head = tmpNode; // if node is added in the beginning then update head

            } else { // if node is added anywhere else

              if (current != NULL) // if node is added in the end then update current, if not, don't update anything
                current = current->next;
            }

          } else { // if list is empty (head = null)
            head = current = add_node(head, head, playerInfo); // set head
          }

        }

        else if (response == 'D')
        {

            printf("\nEnter family name for entry to delete: ");
            safegets(input, MAX_LENGTH+1);
            head = delete_node(head, input);
        }
        else if (response == 'S')
        {


            printf("\nEnter family name to search for: ");
            safegets(input, MAX_LENGTH+1);

            struct node *searched_node = searchByFamily(head, input);

            if (searched_node != NULL) { // if a node is found then display it

              familyNameFound(searched_node->playerInfo.familyName);
              print_player(searched_node);
            }
            else
            {
              familyNameNotFound(input); // if no node is found then display error
            }

        }
        else if (response == 'V')
        {


            printf("\nEnter value: ");
            safegets(input, MAX_LENGTH+1);
            searchByValue(head, atoi(input));



        }
        else if (response == 'P')
        {
            print_all_team(head);
        }
        else if (response == 'Q')
        {

        }
        else
        {
            printf("\nInvalid command.\n%s\n",commandList);
        }
    } while (response != 'Q');


      if (head != NULL) { // if list is not empty
       deletePlayer(playerInfo);
        delete_all_team(head);
        // - - -
        head = NULL;
        current = NULL;
      }


      print_all_team(head);


    return 0;
}

//**********************************************************************
// Support Function Definitions

// Function to get a line of input without overflowing target char array.
void safegets (char s[], int arraySize)
{
    int i = 0, maxIndex = arraySize-1;
    char c;
    while (i < maxIndex && (c = getchar()) != NEWLINE)
    {
        s[i] = c;
        i = i + 1;
    }
    s[i] = NULL_CHAR;
}

// Function to call when user is trying to insert a family name
// that is already in the book.
void familyNameDuplicate (char familyName[])
{
    printf("\nAn entry for <%s> is already in the team!\n"
           "New entry not entered.\n",familyName);
}

// Function to call when a player with this family name was found in the team.
void familyNameFound (char familyName[])
{
    printf("\nThe player with family name <%s> was found in the team.\n",
             familyName);
}

// Function to call when a player with this family name was not found in the team.
void familyNameNotFound (char familyName[])
{
    printf("\nThe player with family name <%s> is not in the team.\n",
             familyName);

}

// Function to call when a family name that is to be deleted
// was found in the team.
void familyNameDeleted (char familyName[])
{
    printf("\nDeleting player with family name <%s> from the team.\n",
             familyName);
}

// Function to call when printing an empty team.
void printTeamEmpty (void)
{
    printf("\nThe team is empty.\n");
}

// Function to call to print title when whole team being printed.
void printTeamTitle (void)
{
    printf("\nMy Team: \n");
}

// Function to call when no player in the team has lower or equal value to the given value
void printNoPlayersWithLowerValue(int value)
{
	printf("\nNo player(s) in the team is worth less than or equal to <%d>.\n", value);
}

//**********************************************************************
// Add your functions below this line.
struct node*  add_node(struct node * head, struct node * list, struct player * value) {

  struct node * new_node, *curr_node, *prev_node = NULL;

  new_node = malloc(sizeof(struct node)); // give memory to new_node to initialize it

  if (new_node == NULL) {
    printf("Error: malloc failed in add_node\n");
    exit(EXIT_FAILURE);
  }

  if (head == NULL) { // if list is empty

    new_node->playerInfo = *value;

    new_node->next = list;


  } else { // if list is not empty

  curr_node = head;


  while (curr_node != NULL) { // keep updating curr and prev until correct position is found

    if (value->position == GOALKEEPER
        && curr_node->playerInfo.position != DEFENDER
        && curr_node->playerInfo.position != MIDFIELDER
        && curr_node->playerInfo.position != STRIKER
       )
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }


    else if (value->position == DEFENDER
             && curr_node->playerInfo.position != MIDFIELDER
             && curr_node->playerInfo.position != STRIKER
            )
    {
      prev_node = curr_node;
      curr_node = curr_node->next;
    }

    else if (value->position == MIDFIELDER
             && curr_node->playerInfo.position != STRIKER
            )
    {
      prev_node = curr_node;
      curr_node = curr_node->next;
    }
    else if (value->position == STRIKER)
    {
      char prev_family[MAX_LENGTH+1], curr_family[MAX_LENGTH+1];


      prev_node = curr_node;
      curr_node = curr_node->next;
    }

    else {

      break;

    }

  }


    if (searchByFamily(head, value->familyName) != NULL) { // to avoid duplicate
      familyNameDuplicate(value->familyName);

    } else {

      if (prev_node == NULL) { // if node is to be added at the begninng (**and list is NOT empty)

        new_node->playerInfo = *value;

        new_node->next = curr_node;


    } else { // if node is not added at the begnining
        new_node->playerInfo = *value;
        new_node->next = curr_node;
        prev_node->next = new_node;
      }

    }
  }

  return new_node;
}



void deletePlayer(struct player * a_player)
{
  free(a_player->familyName);
  free(a_player->firstName);
  free(a_player);
}

void freeNode(struct node *node_to_delete) {
  free(node_to_delete);
}

struct node * delete_node(struct node * head, char familyName[])
{
  struct node *prev_node, *curr_node;


  if (strcmp(head->playerInfo.familyName, familyName) == 0) { // if head matches
    prev_node = head;
    head = prev_node->next;
    free(prev_node);


  } else {  // look through the list

    curr_node = head;

    while (curr_node != NULL && strcmp(curr_node->playerInfo.familyName, familyName) != 0) { // update prev and curr until name matches
      prev_node = curr_node;
      curr_node = curr_node->next;
    }

    if (curr_node != NULL) { // if curr node is found then delete
      prev_node->next = curr_node->next;
      free(curr_node);
      familyNameDeleted(familyName);

    } else { // if family not found, display error
      familyNameNotFound(familyName);
    }
  }

  return head;
}


struct node * searchByFamily(struct node *head, char familyName[]) {
  struct node *curr_node;
  curr_node = head;
  while (curr_node != NULL && strcmp(curr_node->playerInfo.familyName, familyName) != 0) {
    curr_node = curr_node->next;
  }

  return curr_node;
}


void searchByValue(struct node *head, int value) {
  struct node *curr_node = head;
  int flag = 0; // value to indicate whether value found or not

  while (curr_node != NULL) {
    if (curr_node->playerInfo.value <= value) {
      flag = 1;
      printf("\nFamily Name: %s\n",curr_node->playerInfo.familyName);
      printf("First Name: %s\n",curr_node->playerInfo.firstName);
      printf("position: %c\n",curr_node->playerInfo.position);
      printf("value: %d\n",curr_node->playerInfo.value);

    }

    curr_node = curr_node->next;
  }

  if (flag == 0)
    printNoPlayersWithLowerValue(value);
}



void print_player(struct node *searched_node) {
  printf("\nFamily Name: %s\n",searched_node->playerInfo.familyName);
  printf("First Name: %s\n",searched_node->playerInfo.firstName);
  printf("position: %c\n",searched_node->playerInfo.position);
  printf("value: %d\n",searched_node->playerInfo.value);
}

void print_all_team(struct node *head) {

  if (head == NULL) {
    printTeamEmpty();
  }

  else {
    printf("\nMy Team:\n");
  while (head != NULL) {

    printf("\nFamily Name: %s\n",head->playerInfo.familyName);
    printf("First Name: %s\n",head->playerInfo.firstName);
    printf("position: %c\n",head->playerInfo.position);
    printf("value: %d\n",head->playerInfo.value);
    head = head->next;
  }
}


}

void delete_all_team(struct node *head) {
  struct node *curr_node;
  curr_node= head;

  while (head != NULL) {
    curr_node = head;
    freeNode(curr_node);
    head = head->next;
  }

}

void addStringToPlayer(struct player *playerInfo, char *userInput, char type[]) {

  if (strcmp(type, "Family") == 0) {
    playerInfo->familyName = malloc(sizeof(userInput));
    strcpy(playerInfo->familyName, userInput);
  } else {
    playerInfo->firstName = malloc(sizeof(userInput));
    strcpy(playerInfo->firstName, userInput);
  }
}

void updateHeadAndTail(struct node *tmpNode, struct node *head, struct node* current) {

  if (tmpNode->next != NULL // check if node is added in the beginning
      && (strcmp(head->playerInfo.familyName, tmpNode->next->playerInfo.familyName) == 0)
     )
  {
    head = tmpNode; // if node is added in the beginning then update head

  } else { // if node is added anywhere else

    if (current != NULL) // if node is added in the end then update current, if not, don't update anything
      current = current->next;
  }

}
