#include <string.h>
#include <euler/number.h>

int
is_permutation(int n1, int n2)
{
  int nums1[10], nums2[10];

  memset(nums1, 0, sizeof(nums1));
  memset(nums2, 0, sizeof(nums2));

  while(n1) {
    int digit = n1 % 10;
    n1 /= 10;
    nums1[digit]++;
  }
  while(n2) {
    int digit = n2 % 10;
    n2 /= 10;
    nums2[digit]++;
  }
  return !memcmp(nums1, nums2, sizeof(nums1));
}


