#pragma once

#include "sort.h"
#include "../../../TotalAreaComparator.h"
#include "../unsorted_sequence_table.h"

namespace structures
{

	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typeparam>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typeparam>
	template <typename K, typename T>
	class QuickSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> UnsortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table, Comparator<T>* comparator) override;
	private:
		void quick(int min, int max, UnsortedSequenceTable<K, T>& table, Comparator<T>* comparator);
	};

	template<typename K, typename T>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>& table, Comparator<T>* comparator)
	{
		quick(0, table.size() - 1, table, comparator);
	}

	template<typename K, typename T>
	inline void QuickSort<K, T>::quick(int min, int max, UnsortedSequenceTable<K, T>& table, Comparator<T>* comparator)
	{
		K pivot = table.getItemAtIndex((min + max) / 2).getKey();
		//T pivot = table.getItemAtIndex((min + max) / 2);
		int lavy = min;
		int pravy = max;

		do {
			//while (comparator->compare(table.getItemAtIndex(lavy), pivot)) {
			while (table.getItemAtIndex(lavy).getKey() < pivot) {
				lavy++;
			}

			while (table.getItemAtIndex(pravy).getKey() > pivot) {
				pravy--;
			}

			if (lavy <= pravy) {
				table.swap(table.getItemAtIndex(lavy), table.getItemAtIndex(pravy));
				lavy++;
				pravy++;
				notify();
			}
		} while (lavy <= pravy);

		if (min < pravy) {
			quick(min, pravy, table, comparator);
		}
		if (lavy < max) {
			quick(lavy, max, table, comparator);
		}
	}

}