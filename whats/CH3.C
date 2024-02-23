GPU:
GPUs are massively multithreaded many core chips: الكرت له اكثر من بروسيسر والسبي يو عنده بروسيسر واحد
  handle computation only for computer graphics
  Hundreds of processors
  Tens of thousands of concurrent threads
  TFLOPs peak performance
  Fine-grained data-parallel computation

GPGPU:(هو اللي يسمح لك في انك تستخدم الاشياء اللي يسويها ال CPU)
  General purpose computing on GPUs

  GPGPU is the use of a GPU, which typically
  handles computation only for computer
  graphics, to perform computation in
  applications traditionally handled by the
  central processing unit (CPU).

Why GPGPU:
   Massively parallel computing power
   Inexpensive
--------------------------------------------------------------------------------
What is CUDA:
  CUDA is the acronym for Compute Unified Device
  Architecture.

  A parallel computing architecture developed by NVIDIA.

  The computing engine in GPU

  CUDA gives developers access to the instruction set
  and memory of the parallel computation elements in
  GPUs

Heterogeneous Computing:(First is the serial code its run in host then the parallel code its rung in Device after that we back in serial code in the host)
  Host:The CPU and its memory (host memory)
  Device:The GPU and its memory (device memory)
--------------------------------------------------------------------------------
CUDA Kernels and Threads:
A Kernel is a Function that runs on a device (الكيرنل فنشكن ما تشتغل بارليل بس ان الفنشك الواحد فيه اكثر من ثريدز)
    One kernel is executed at a time
    Many threads execute each kernel

Differences between CUDA and CPU threads:
    CUDA threads are extremely lightweight
    Very little creation overhead
    Instant switching
--------------------------------------------------------------------------------
CUDA Programming Model:
  A kernel is executed by a grid of thread blocks

  A thread block is a batch of threads that can
  cooperate with each other by:
      Sharing data through shared memory
      Synchronizing their execution

  Threads from different blocks cannot cooperate

  All threads within a block can:
      Share data through ‘Shared Memory’
      Synchronize using ‘_syncthreads()’

  Threads and Blocks have unique IDs

how to executing:
- SIMT
- Threads run in groups of 32 called warps
- Every thread in a warp executes the same instruction at a time

Single Instruction Multiple Thread (SIMT) Execution: هو عبارة عن كيو  من الوارب وكيو من البروسيسر كل بروسي ياخذ وارب ويشتغل عليها بعدين يرجعها للكيو
• Groups of 32 threads formed into warps:
    o always executing same instruction
    o share instruction fetch/dispatch
    o some become inactive
      when code path diverges
    o hardware automatically handles divergence

• Warps are primitive unit of scheduling
    • all warps from all active blocks are time-slice
--------------------------------------------------------------------------------
Simple Procesing Flow(اول شيء ينقل الداتا من السبي يو الى الجبيو  بعدين يشغل البرنامد في الجبيو بعدها يرجع النتائج من الجيبويو الى السيبيو ):
1. Copy input data from CPU memory to GPU memory
2. Run the gpu program and executed
3. Copy result from gpu to cpu
--------------------------------------------------------------------------------
Memory Model:

Registers
o on chip
o fast access
o per thread
o limited amount
o 32 bit

Local Memory
o in DRAM
o slow
o non-cached
o per thread
o relative large


Shared Memory
o on chip
o fast access
o per block
o 16 KByte
o synchronize between
threads


Global Memory
o in DRAM
o slow
o non-cached
o per grid
o communicate between grids


Constant Memory(هنا كاتش عشانها ريد اونلي + نقلل الريدندننسي)
o in DRAM
o cached
o per grid
o read-only


Texture Memory (من اسمها texture )
o in DRAM
o cached
o per grid
o read-only
