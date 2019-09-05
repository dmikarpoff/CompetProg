#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

enum {
 kMemSize = 125000,
 kChunkSize = 7,
 kStackNum = 1000
};

int memory[kMemSize];
int tails[kStackNum];
int sz[kStackNum];
int free_list;

typedef struct Chunk
{
  int parent;
  int data[kChunkSize];
} Chunk;

void init_memory()
{
  for (int i = 0; i < kStackNum; ++i)
  {
    sz[i] = 0;
    tails[i] = -1;
  }
  free_list = 0;
  for (int i = 0; i + kChunkSize + 1 < kMemSize; i += kChunkSize + 1)
  {
    memory[i] = i + kChunkSize + 1;
  }
}

int main()
{
    int n;
    scanf("%d", &n);
    init_memory();
    for (int i = 0; i < n; ++i)
    {
      char command[10];
      int stack_num;
      scanf("%s", command);
      if (command[1] == 'U') {
        int val;
        scanf("%d%d", &stack_num, &val);
        Chunk* cur_chunk = NULL;
        if (sz[stack_num] % kChunkSize == 0)
        {
          Chunk* chunk = (Chunk*)(memory + free_list);
          int idx = free_list;
          free_list = chunk->parent;
          chunk->parent = tails[stack_num];
          tails[stack_num] = idx;
          cur_chunk = chunk;
        }
        else
        {
          cur_chunk = (Chunk*)(memory + tails[stack_num]);
        }
        cur_chunk->data[sz[stack_num] % kChunkSize] = val;
        sz[stack_num] += 1;
        continue;
      }
//      assert(strcmp(command, "POP") == 0);
      scanf("%d", &stack_num);
      int tail = tails[stack_num];
      Chunk* chunk = (Chunk*)(memory + tail);
      printf("%d\n", chunk->data[(sz[stack_num] - 1) % kChunkSize]);
      if (sz[stack_num] % kChunkSize == 1)
      {
        tails[stack_num] = chunk->parent;
        chunk->parent = free_list;
        free_list = tail;
      }
      sz[stack_num] -= 1;
    }
    return 0;
}
