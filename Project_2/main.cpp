#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

FILE *outfile;

class itemNode {
public:
  char name[50];
  int count;
  itemNode *left, *right;

  itemNode() {
    name[0] = '\0';
    count = 0;
    left = NULL;
    right = NULL;
  }

  itemNode(char itemName[], int population) {
    strcpy(name, itemName);
    count = population;
    left = NULL;
    right = NULL;
  }
};

class treeNameNode {
public:
  char treeName[50];
  treeNameNode *left, *right;
  itemNode *theTree;

  treeNameNode() {
    treeName[0] = '\0';
    theTree = NULL;
    left = NULL;
    right = NULL;
  }

  treeNameNode(char name[]) {
    strcpy(treeName, name);
    theTree = NULL;
    left = NULL;
    right = NULL;
  }
};

void printBoth(const char *format, ...) {
  va_list argsConsole;
  va_start(argsConsole, format);
  vprintf(format, argsConsole);
  va_end(argsConsole);

  va_list argsFile;
  va_start(argsFile, format);
  vfprintf(outfile, format, argsFile);
  va_end(argsFile);
}

treeNameNode *insertName(treeNameNode *root, char name[]) {
  if (root == NULL) {
    return new treeNameNode(name);
  }

  if (strcmp(name, root->treeName) < 0) {
    root->left = insertName(root->left, name);
  } else if (strcmp(name, root->treeName) > 0) {
    root->right = insertName(root->right, name);
  }

  return root;
}

itemNode *insertItem(itemNode *root, char name[], int count) {
  if (root == NULL) {
    return new itemNode(name, count);
  }

  if (strcmp(name, root->name) < 0) {
    root->left = insertItem(root->left, name, count);
  } else if (strcmp(name, root->name) > 0) {
    root->right = insertItem(root->right, name, count);
  }

  return root;
}

treeNameNode *searchNameNode(treeNameNode *root, char treeName[50]) {
  if (root == NULL || strcmp(treeName, root->treeName) == 0) {
    return root;
  }

  if (strcmp(treeName, root->treeName) < 0) {
    return searchNameNode(root->left, treeName);
  } else {
    return searchNameNode(root->right, treeName);
  }
}

itemNode *searchItemNode(itemNode *root, char name[]) {
  if (root == NULL || strcmp(name, root->name) == 0) {
    return root;
  }

  if (strcmp(name, root->name) < 0) {
    return searchItemNode(root->left, name);
  } else {
    return searchItemNode(root->right, name);
  }
}

void printItemsInorder(itemNode *root) {
  if (root == NULL) {
    return;
  }

  printItemsInorder(root->left);
  printBoth("%s ", root->name);
  printItemsInorder(root->right);
}

void printNamesInorder(treeNameNode *root) {
  if (root == NULL) {
    return;
  }

  printNamesInorder(root->left);
  printBoth("%s ", root->treeName);
  printNamesInorder(root->right);
}

void traverse_in_traverse(treeNameNode *root) {
  printNamesInorder(root);
  printBoth("\n");

  if (root == NULL) {
    return;
  }

  traverse_in_traverse(root->left);

  printBoth("***%s***\n", root->treeName);
  printItemsInorder(root->theTree);
  printBoth("\n");

  traverse_in_traverse(root->right);
}

void printItemTreesOnly(treeNameNode *root) {
  if (root == NULL) {
    return;
  }

  printItemTreesOnly(root->left);

  printBoth("***%s***\n", root->treeName);
  printItemsInorder(root->theTree);
  printBoth("\n");

  printItemTreesOnly(root->right);
}

void printAllTrees(treeNameNode *root) {
  printNamesInorder(root);
  printBoth("\n");

  printItemTreesOnly(root);
}

int countItems(itemNode *root) {
  if (root == NULL) {
    return 0;
  }

  return root->count + countItems(root->left) + countItems(root->right);
}

int itemsBefore(itemNode *root, char target[]) {
  if (root == NULL) {
    return 0;
  }

  int total =
      itemsBefore(root->left, target) + itemsBefore(root->right, target);

  if (strcmp(root->name, target) < 0) {
    total = total + 1;
  }

  return total;
}

int treeHeight(itemNode *root) {
  if (root == NULL) {
    return 0;
  }

  int leftHeight = treeHeight(root->left);
  int rightHeight = treeHeight(root->right);

  if (leftHeight > rightHeight) {
    return 1 + leftHeight;
  } else {
    return 1 + rightHeight;
  }
}

treeNameNode *buildNameTree(FILE *infile, int N) {
  treeNameNode *root = NULL;
  char nameBuffer[50];

  for (int i = 0; i < N; i++) {
    fscanf(infile, "%s", nameBuffer);
    root = insertName(root, nameBuffer);
  }

  return root;
}

void buildItemTrees(FILE *infile, treeNameNode *nameRoot, int I) {
  char treeName[50];
  char itemName[50];
  int itemCount;

  for (int i = 0; i < I; i++) {
    fscanf(infile, "%s %s %d", treeName, itemName, &itemCount);

    treeNameNode *target = searchNameNode(nameRoot, treeName);

    if (target != NULL) {
      target->theTree = insertItem(target->theTree, itemName, itemCount);
    }
  }
}

void processSearch(treeNameNode *nameRoot, char treeName[], char itemName[]) {
  treeNameNode *target = searchNameNode(nameRoot, treeName);

  if (target == NULL) {
    printBoth("%s does not exist\n", treeName);
    return;
  }

  itemNode *found = searchItemNode(target->theTree, itemName);

  if (found != NULL) {
    printBoth("%d %s found in %s\n", found->count, itemName, treeName);
  } else {
    printBoth("%s not found in %s\n", itemName, treeName);
  }
}

void processItemBefore(treeNameNode *nameRoot, char treeName[],
                       char itemName[]) {
  treeNameNode *target = searchNameNode(nameRoot, treeName);

  if (target == NULL) {
    printBoth("%s does not exist\n", treeName);
    return;
  }

  int before = itemsBefore(target->theTree, itemName);
  printBoth("item before %s: %d\n", itemName, before);
}

void processHeightBalance(treeNameNode *nameRoot, char treeName[]) {
  treeNameNode *target = searchNameNode(nameRoot, treeName);

  if (target == NULL) {
    printBoth("%s does not exist\n", treeName);
    return;
  }

  int leftHeight = 0;
  int rightHeight = 0;

  if (target->theTree != NULL) {
    leftHeight = treeHeight(target->theTree->left);
    rightHeight = treeHeight(target->theTree->right);
  }

  int difference = leftHeight - rightHeight;
  if (difference < 0) {
    difference = -difference;
  }

  if (difference > 1) {
    printBoth(
        "%s: left height %d, right height %d, difference %d, not balanced\n",
        treeName, leftHeight, rightHeight, difference);
  } else {
    printBoth("%s: left height %d, right height %d, difference %d, balanced\n",
              treeName, leftHeight, rightHeight, difference);
  }
}

void processCount(treeNameNode *nameRoot, char treeName[]) {
  treeNameNode *target = searchNameNode(nameRoot, treeName);

  if (target == NULL) {
    printBoth("%s does not exist\n", treeName);
    return;
  }

  int total = countItems(target->theTree);
  printBoth("%s count %d\n", treeName, total);
}

int main() {
  FILE *infile = fopen("in.txt", "r");
  outfile = fopen("out.txt", "w");

  if (infile == NULL || outfile == NULL) {
    std::cout << "Error opening files." << std::endl;
    return 1;
  }

  int N, I, Q;
  fscanf(infile, "%d %d %d", &N, &I, &Q);

  treeNameNode *nameRoot = buildNameTree(infile, N);

  buildItemTrees(infile, nameRoot, I);

  printAllTrees(nameRoot);

  char command[50];
  char treeName[50];
  char itemName[50];

  for (int i = 0; i < Q; i++) {
    fscanf(infile, "%s", command);

    if (strcmp(command, "search") == 0) {
      fscanf(infile, "%s %s", treeName, itemName);
      processSearch(nameRoot, treeName, itemName);
    } else if (strcmp(command, "item_before") == 0) {
      fscanf(infile, "%s %s", treeName, itemName);
      processItemBefore(nameRoot, treeName, itemName);
    } else if (strcmp(command, "height_balance") == 0) {
      fscanf(infile, "%s", treeName);
      processHeightBalance(nameRoot, treeName);
    } else if (strcmp(command, "count") == 0) {
      fscanf(infile, "%s", treeName);
      processCount(nameRoot, treeName);
    }
  }

  fclose(infile);
  fclose(outfile);

  return 0;
}
