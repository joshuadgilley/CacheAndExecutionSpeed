Timing Linux Cache & Main Memory Experiment

Questions to answer:
How big is a cache block? 
How big is the cache?
How long does a reference to main memory take to complete?
How long does a reference that can be satisfied from cache take to complete? 

We built four functions to answer these four questions. Before building these four functions we wanted to make sure that the output we were receiving was 
correct relative to our machines. So we built a function called “read()”. The idea behind this function is to pass our output from the future functions, 
getting our results and comparing those to the contents in our cpuinfo section of the /proc file system. 
Next, we set out to answer the aforementioned questions. 

To answer question three, we built a function called “getAvgTimeMain()”. The idea behind this function is to create an array of a fixed size, populating the 
array, and reading values skipping through the array according to block size. This allows us to pull from main memory every time. All the while, we spent the total 
time elapsed to iterate the array. We then divide by the number passed in which indicates the total number of times we want to run this process, to get an average. 

To answer question four, we built a function called “getAvgTimeCache()”. This function is similar to getAvgTimeMain, except it is accessing the same element of the 
array over and over as to pull from the cache instead of main memory. We time this process similarly to the timing functionality described in the previous paragraph. 

To answer question one, we initially started with experimentation plugging in various sizes that we thought might be the block size. After a few iterations of this process 
using different block sizes, we found that plugging in 32 yielded more time elapsed than plugging in 31 for instance. This showed us that the block size is most 
likely 32, so we created a function that tested out theory. During our experimentation we found that when comparing the reference to main memory with the reference to 
“cache” we had similar results until reaching 32. So the getCacheBlockSize function tests various sizes from 1 to 256 searching for a massive difference between the time 
elapsed in referencing main memory vs the cache. 

	The last question we will cover, number 2, was an interesting experience full of rabbit holes, and hours of experimentation. We will cover the few rabbit holes we experimented with. 
-- Right-to-left method --
We figured that as the cache is being filled with values, storing the values first in first out where the values at the end of the array fill the cache. 
Since in our minds the right side of the array would be cached, we could test different values from the right side to see where the access time increased significantly 
showing us that we had reached outside of the saved values.
After implementing the idea we found that we needed to access the value only one time after loading the array so as to not load values around it into the cache.
To do this we instantiate the array and then only look for one value before instantiating the array again. With this method we were not able to see any huge increase in time and we then scrapped this method.
-- Different array sizes method --
In this method we thought to have multiple arrays of different sizes ranging from 4000, 8000, 16000, and 32000.
The reason we chose these numbers is because 16KB is 16000 bytes and an int is 4 bytes. Therefore, we took 16000/4 which gave us 8000. We did the same calculation for 32KB, 64KB, and 128KB.
After creating the different array sizes and averaging the time it took to access and single element we saw no difference between the different size arrays.
We then decided to try 2^n where n was between 0 and 20 and found that all of those arrays also had the same access time as well.
SInce we were having no luck with this method as well we decided to shift to our current implementation which is described below.
-- Final method --
Create MAX_CACHE to act as a ceiling for potential cache sizes 
Create a large array and to go through the array a fixed number of steps, but accessing the same index in the array repeatedly. So first 1 step, then 2, 4, 8, 16 and so on. 
The idea here being that when we reach our cache size, the elapsed time will drop off significantly. When that happens, we’ve found our size. 
