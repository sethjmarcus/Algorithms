# Ari Rosenbloom, Seth Marcus Code Explanation

1. Question 00 (Set up)

   1. First we create the table if it doesn't exist. As to why the data types are different than what Prof. Zombory posted, see [this link](https://docs.google.com/document/d/1K2mnWOfszwRu_a0UL__9gnDFcZoTAjS7gW1i7_9Y_lM/edit?usp=sharing).
   2. Then we populate the table.

2. Question 01

   1. We select the `count` of `distinct` values from all the columns, named individually and aliased, from the desired table.
      1. This results in 1 row and 17 columns, but is a single select statement that, in our opinion, is much more elegant than the alternative
   2. The Commented out query
      1. We don't have enough space to execute this query, but based on small scale testing on another table, this should produce the desired result.
   3. What we can deduce from these results and the row count achieved in hw03 is that there is no single attribute that can serve as a primary key on it’s own.
   4. ![](https://github.com/bzombory/QC_Math_290_Spring_2021/blob/main/homeworks/hw04/submissions/3/Hw04Pictures/01a.jpeg)
   5. 

3. Question 02:

   1. First we return all distinct tuples that have a unique set of the 17 attributes.

   2. Then we take a `count` of these entries.

   3. There is no single attribute that can serve as a stand alone primary key. There may exist a combination of attributes that can serve as a composite key, but there is no obvious composite key in the table. More specifically, we are not testing all  possible 
      $$
      \sum_{i=1}^{17} {17\choose{i}}
      $$
      combinations to try to find this composite key. Use a surrogate key (see [wiki link](https://en.wikipedia.org/wiki/Surrogate_key) for more information).
      
   4. ![01b1](C:\Users\sethj\Downloads\Hw04Pictures\01b1.jpeg)

   ![01b2](C:\Users\sethj\Downloads\Hw04Pictures\01b2.jpeg)

4. Question 03:

   1. Selecting the requested tuples from the table using a `where` clause.

      ![03a](C:\Users\sethj\Downloads\Hw04Pictures\03a.png)

   2. Selecting distinct trips where `passenger_count>3` then taking a `count` of the results.

      ​	![3b](C:\Users\sethj\Downloads\Hw04Pictures\3b.png)

   3. Taking a `count` of the  tuples that are in between these times.

      ​	![3c](C:\Users\sethj\Downloads\Hw04Pictures\3c.jpeg)

   4. Similar to 2 (above). Only difference is the `where` clause to match the requested parameters.

      ![3d](C:\Users\sethj\Downloads\Hw04Pictures\3d.png)

   5. Similar to 4 (above). Only difference is the `where` clause to match the (more complicated) requested parameters.

      ![3e](C:\Users\sethj\Downloads\Hw04Pictures\3e.png)

   6. Used the `sum()` function to get the sum of all the recorded tips.

      ​	![03f](C:\Users\sethj\Downloads\Hw04Pictures\03f.png)

      1. *Can you assume that the answer to your previous question is equivalent to the question of "How much tip did taxi drivers collected in total in 2018?" Explain your answer.*
         1. No. Cash, gift cards, sex, and any other undocumented form of a tip are not included in this total.

5. Question 04:

   1. | folder_name | size                 |
      | ----------- | -------------------- |
      | base        | 17,405,569,124 bytes |
      | databaseid  | 17,381,544,495 bytes |

   2. Delete all the records with a `where` clause on the requested parameter.

   3. queried a `count` of how many records have the attributed that was just deleted.

      1. returned 0 as expected.

   4. | folder_name | size                 |
      | ----------- | -------------------- |
      | base        | 17,407,535,204 bytes |
      | databaseid  | 17,383,535,151 bytes |

   5. Despite deleting tuples, they were only soft deleted and not hard deleted. What this means in practice is that these tuples are still in the database, but they are no longer readable by the user. This is useful for when you accidently delete tuples you shouldn't have, so it is easier to restore them. However, multiple transactions occurred, which were recorded, thereby increasing the size of the overall database.

6. Question 05:

   1. | folder_name | size                |
      | ----------- | ------------------- |
      | base        | 7,762,313,216 bytes |
      | databaseid  | 7,738,270,211 bytes |

   2. We actually removed the tuples from the database. So now the database overall is much smaller, but if we need those tuples back, it is now much more difficult as they *really* aren't there.

7. Question 06:

   1. Truncate the table using the `truncate` command.
   2. Recopy the table.

