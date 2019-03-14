#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures
{

	/// <summary> Triedenie Shell sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typeparam>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typeparam>
	template <typename K, typename T>
	class ShellSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Shell sort. </summary>
		/// <param name = "table"> UnsortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table, Comparator<T>* comparator) override;

	private:
		void shell(int krok, UnsortedSequenceTable<K, T>& table, Comparator<T>* comparator);
	};

	template<typename K, typename T>
	inline void ShellSort<K, T>::sort(UnsortedSequenceTable<K, T>& table, Comparator<T>* comparator)
	{
		shell(log10(table.size()), table, comparator);
	}

	template<typename K, typename T>
	inline void ShellSort<K, T>::shell(int krok, UnsortedSequenceTable<K, T>& table, Comparator<T>* comparator)
	{
		int j;
		for (int delta = 0; delta < krok; delta++) {
			for (int i = delta; i < table.size(); i += krok) {
				j = i;
				// <
				while ((j - krok >= delta) && (!comparator->compare(table.getItemAtIndex(j).accessData(), table.getItemAtIndex(j - krok).accessData()))) {
					table.swap(table.getItemAtIndex(j), table.getItemAtIndex(j - krok));
					j -= krok;
					notify();
				}
			}
		}

		if (krok > 1) {
			shell(krok - 1, table, comparator);
		}
	}
}