// algorithm standard header

#ifndef ALGORITHM
#define ALGORITHM

namespace MyNamespace
{

   template< typename RanIt, typename Ty, typename Pr >
   inline void pushHeapByIndex( RanIt first, ptrdiff_t hole, ptrdiff_t top, Ty &val, Pr pred )
   {
       //while (hole != top && pred(*(first + (hole - 1) / 2), val))//*(first + (hole - 1) / 2) < val  不行用
       //{
       //    /*ptrdiff_t cur = (hole - 1) / 2;
       //    RanIt last = first + hole;
       //    *last = *(first + cur);
       //    hole = cur;*/
       //    *(first + hole) = *(first + (hole - 1) / 2);
       //    hole = (hole - 1) / 2;
       //}
       //*(first + hole) = val;

       //auto i = (hole - 1) / 2; // parent
       //while (hole > top && pred(first[i], val)) first[hole] = first[i], i = ((hole = i) - 1) / 2;
       //first[hole] = val;



       /*while (hole != top && pred(*(first + (hole - 1) / 2), val))
       {
           *(first + hole) = *(first + (hole - 1) / 2);
           hole = (hole - 1) / 2;
       }
       *(first + hole) = val;*/



       while (hole != top && pred(*(first + (hole - 1) / 2), val))
       {
           *(first + hole) = *(first + (hole - 1) / 2);
           hole = (hole - 1) / 2;
       }
       *(first + hole) = val;
   }

   // push *(last - 1) onto heap at [first, last - 1), using pred
   template< typename RanIt, typename Pr >
   inline void push_heap( RanIt first, RanIt last, Pr pred )
   {
      ptrdiff_t count = last - first;
      if( count >= 2 )
      {
         --last;
         typename RanIt::value_type val = *last;
         --count;
         pushHeapByIndex( first, count, 0, val, pred );
      }
   }

   template< typename RanIt, typename Ty, typename Pr >
   inline void popHeapHoleByIndex( RanIt first, ptrdiff_t hole, ptrdiff_t bottom, Ty &val, Pr pred )
   {
       //ptrdiff_t top = hole;
       //
       //while (hole * 2 + 1 < bottom)//max heap
       //{
       //    int leftchild = (hole * 2) + 1;
       //    int rightchild = (hole * 2) + 2;
       //    RanIt leftchildren = first + leftchild;
       //    RanIt rightchildren = first + rightchild;
       //    if (rightchild == bottom || pred(*rightchildren, *leftchildren))//*rightchildren<*leftchildren也不能
       //    {
       //        *(first + hole) = *leftchildren;
       //        hole = leftchild;
       //    }
       //    else
       //    {
       //        *(first + hole) = *rightchildren;
       //        hole = rightchild;
       //    }
       //}

       //auto top = hole, i = hole * 2 + 2; // i -> right child
       //for (; i < bottom; i = (hole = i) * 2 + 2)
       //    first[hole] = first[pred(first[i], first[i - 1]) ? --i : i];
       //// if only have left child
       //if (i-- == bottom) first[hole] = first[i], hole = i;



       //ptrdiff_t top = hole;
       //while (hole * 2 + 1 < bottom)//max heap
       //{
       //    int leftchild = (hole * 2) + 1;
       //    int rightchild = (hole * 2) + 2;
       //    RanIt leftchildren = first + leftchild;
       //    RanIt rightchildren = first + rightchild;
       //    if (rightchild == bottom || pred(*rightchildren, *leftchildren))//若rightchild==bottom 時要無條件取左邊
       //    {
       //        *(first + hole) = *leftchildren;
       //        hole = leftchild;
       //    }
       //    else
       //    {
       //        *(first + hole) = *rightchildren;
       //        hole = rightchild;
       //    }
       //}

       auto top = hole;
       while (hole * 2 + 1 < bottom)
       {
           int left = hole * 2 + 1;
           int right = hole * 2 + 2;
           if (right == bottom || pred(*(first + right), *(first + left)))
           {
               *(first+hole)=*(first+left);
               hole=left;
           }
           else
           {
               *(first + hole) = *(first + right);
               hole = right;
           }
       }










       pushHeapByIndex(first, hole, top, val, pred);
   }

   // pop *first to *(last - 1) and reheap, using pred
   template< typename RanIt, typename Pr >
   inline void pop_heap( RanIt first, RanIt last, Pr pred )
   {
      if( last - first >= 2 )
      {
         --last;
         typename RanIt::value_type val = *last;

         // pop *first to *(last - 1) and reheap, using pred
         // precondition: first != last
         *last = *first;
         popHeapHoleByIndex( first, 0, last - first, val, pred );
      }
   }

   // make [first, last) into a heap, using pred
   template< typename RanIt, typename Pr >
   inline void make_heap( RanIt first, RanIt last, Pr pred )
   {
      ptrdiff_t bottom = last - first;
      ptrdiff_t hole = bottom / 2;
      while( hole > 0 )
      {
         // reheap top half, bottom to top
         --hole;
         typename RanIt::value_type val = *( first + hole );
         popHeapHoleByIndex( first, hole, bottom, val, pred );
      }
   }
}

#endif // ALGORITHM