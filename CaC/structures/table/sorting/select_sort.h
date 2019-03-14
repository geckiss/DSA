#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures
{

	/// <summary> Triedenie Select sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typeparam>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typeparam>
	template <typename K, typename T>
	class SelectSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Select sort. </summary>
		/// <param name = "table"> UnsortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

	template<typename K, typename T>
	inline void SelectSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		int min;
		for (int i = 0; i < table.size() - 1; i++) {
			min = i;
			for (int j = i + 1; j < table.size(); j++) {
				if (table.getItemAtIndex(j).getKey() < table.getItemAtIndex(min).getKey()) {
					min = j;
				}
				table.swap(table.getItemAtIndex(i), table.getItemAtIndex(min));
				notify();
			}
		}
	}

}