#include <stdio.h>
#include "../tree/tree.h"

/* Prosedur membuat kicauan baru */
AddressKicauan newNodeKicauan(Kicauan kicauan)
/* I.S. Sembarang */
/* F.S. Bila alokasi berhasil, terbentuk alokasi node kicauan baru
  Bila alokasi gagal, F.S.=I.S. */
{
  // Alokasi
  AddressKicauan newNode = (AddressKicauan)malloc(sizeof(Kicauan));

  // Alokasi berhasil
  if (newNode != NULL)
  {
    InfoKicauan(newNode) = kicauan;
    FirstLeftChildBalasan(newNode) = NULL;
  }

  return newNode;
}

/* Prosedur membuat balasan baru */
AddressBalasan newNodeBalasan(Balasan balasan)
/* I.S. Sembarang */
/* F.S. Bila alokasi berhasil, terbentuk alokasi node balasan baru
  Bila alokasi gagal, F.S.=I.S. */
{
  // Alokasi
  AddressBalasan newNode = (AddressBalasan)malloc(sizeof(Balasan));

  // Alokasi berhasil
  if (newNode != NULL)
  {
    InfoBalasan(newNode) = balasan;
    LeftChildBalasan(newNode) = NULL;
    RightSiblingBalasan(newNode) = NULL;
  }

  return newNode;
}

/* Prosedur untuk mengecek apakah ada balasan */
boolean isBalasanExist(TreeKicauan nodeKicauan)
/* Mengembalikan true bila ada balasan, mengembalikan false bila tidak ada balasan */
{
  return (FirstLeftChildBalasan(nodeKicauan) != NULL);
}

/* Dapatkan node balasan dengan id terbesar (latest balasan) */
/* Menghasilkan node balasan dengan id terbesar */
/* Menghasilkan null bila tidak ada */
AddressBalasan getLatestBalasan(TreeKicauan nodeKicauan)
{
  // Kasus tidak ada balasan
  if (!isBalasanExist(nodeKicauan))
  {
    return NULL;
  }

  // Kasus ada balasan
  AddressBalasan nodeBalasan = FirstLeftChildBalasan(nodeKicauan);
  return getLatestBalasanRecursive(nodeBalasan);
}
AddressBalasan getLatestBalasanRecursive(AddressBalasan nodeBalasan)
{
  AddressBalasan leftChild = LeftChildBalasan(nodeBalasan);
  AddressBalasan rightSibling = RightSiblingBalasan(nodeBalasan);

  // Kasus tidak ada left child dan right sibling
  if (leftChild == NULL && rightSibling == NULL)
  {
    return nodeBalasan;
  }

  // Kasus ada left child tidak ada right sibling
  if (leftChild != NULL && rightSibling == NULL)
  {
    AddressBalasan maxLeftChild = getLatestBalasanRecursive(leftChild);
    if (ID(InfoBalasan(maxLeftChild)) > ID(InfoBalasan(nodeBalasan)))
    {
      return maxLeftChild;
    }
    else
    {
      return nodeBalasan;
    }
  }

  // Kasus tidak ada left child ada right sibling
  if (leftChild == NULL && rightSibling != NULL)
  {
    AddressBalasan maxRightSibling = getLatestBalasanRecursive(rightSibling);
    if (ID(InfoBalasan(maxRightSibling)) > ID(InfoBalasan(nodeBalasan)))
    {
      return maxRightSibling;
    }
    else
    {
      return nodeBalasan;
    }
  }

  // Kasus ada left child dan right sibling
  if (leftChild != NULL && rightSibling != NULL)
  {
    AddressBalasan maxLeftChild = getLatestBalasanRecursive(leftChild);
    AddressBalasan maxRightSibling = getLatestBalasanRecursive(rightSibling);

    if (ID(InfoBalasan(maxLeftChild)) > ID(InfoBalasan(maxRightSibling)))
    {
      if (ID(InfoBalasan(maxLeftChild)) > ID(InfoBalasan(nodeBalasan)))
      {
        return maxLeftChild;
      }
      else
      {
        return nodeBalasan;
      }
    }
    else
    {
      if (ID(InfoBalasan(maxRightSibling)) > ID(InfoBalasan(nodeBalasan)))
      {
        return maxRightSibling;
      }
      else
      {
        return nodeBalasan;
      }
    }
  }
}

/* Dapatkan node balasan pada kicauan dengan id tertentu */
/* Mengembalikan node bila ketemu, mengembalika NULL bisa tidak ketemu */
/* Untuk mengecek seluruh node, input: firstLeftChild dari kicauan */
AddressBalasan getBalasan(TreeKicauan nodeKicauan, int idBalasan)
{
  // Kasus tidak ada balasan
  if (!isBalasanExist(nodeKicauan))
  {
    return NULL;
  }

  // Kasus idBalasan tidak valid
  if (idBalasan < 1)
  {
    return NULL;
  }

  // Kasus ada balasan
  AddressBalasan nodeBalasan = FirstLeftChildBalasan(nodeKicauan);
  return getBalasanRecursive(nodeBalasan, idBalasan);
}
AddressBalasan getBalasanRecursive(AddressBalasan nodeBalasan, int idBalasan)
{
  // Kasus nodeBalasan merupakan node yang dicari
  if (ID(InfoBalasan(nodeBalasan)) == idBalasan)
  {
    return nodeBalasan;
  }

  // Kasus nodeBalasan bukan merupakan node yang dicari, cek left child & right sibling
  AddressBalasan leftChild = LeftChildBalasan(nodeBalasan);
  AddressBalasan rightSibling = RightSiblingBalasan(nodeBalasan);

  // Kasus currentNode bukan value yang dicair,
  // dan tidak ada left child dan right sibling
  if (leftChild == NULL && rightSibling == NULL)
  {
    return NULL;
  }

  AddressBalasan nodeBalasanLeftChild = getBalasanRecursive(leftChild, idBalasan);
  AddressBalasan nodeBalasanRightSibling = getBalasanRecursive(rightSibling, idBalasan);

  // Ketemu di left child
  if (nodeBalasanLeftChild != NULL)
  {
    return nodeBalasanLeftChild;
  }

  // Ketemu di right
  if (nodeBalasanRightSibling != NULL)
  {
    return nodeBalasanRightSibling;
  }

  // Tidak ketemu
  return NULL;
}
