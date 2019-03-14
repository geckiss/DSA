#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"
#include "../../queue/explicit_queue.h"

namespace structures
{

	/// <summary> Triedenie Merge sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class MergeSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Merge sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
	private:
		void rozdel(int n, ExplicitQueue<TableItem<K, T>*>* spoj, ExplicitQueue<TableItem<K, T>*>* rozdel1, ExplicitQueue<TableItem<K, T>*>* rozdel2);

		void spoj(int n, ExplicitQueue<TableItem<K, T>*>* spoj, ExplicitQueue<TableItem<K, T>*>* rozdel1, ExplicitQueue<TableItem<K, T>*>* rozdel2);
	};

	template<typename K, typename T>
	inline void MergeSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		ExplicitQueue<TableItem<K, T>*>* frontRozdel1 = new ExplicitQueue<TableItem<K, T>*>();
		ExplicitQueue<TableItem<K, T>*>* frontRozdel2 = new ExplicitQueue<TableItem<K, T>*>();
		ExplicitQueue<TableItem<K, T>*>* frontSpoj = new ExplicitQueue<TableItem<K, T>*>();
		int i;
		for (TableItem<K, T>* par : table) {
			frontSpoj->push(par);
		}
		i = 1;

		while (i < table.size()) {
			rozdel(i, frontSpoj, frontRozdel1, frontRozdel2);
			spoj(i, frontSpoj, frontRozdel1, frontRozdel2);
			i *= 2;
		}

		rozdel(i, frontSpoj, frontRozdel1, frontRozdel2);
		spoj(i, frontSpoj, frontRozdel1, frontRozdel2);

		table.clear();
		TableItem<K, T>* par;
		while (frontSpoj->size() != 0) {
			par = frontSpoj->pop();
			table.insert(par->getKey(), par->accessData());
		}

		frontSpoj->clear();
		frontRozdel1->clear();
		frontRozdel2->clear();

		delete frontSpoj;
		delete frontRozdel1;
		delete frontRozdel2;
	}

	template<typename K, typename T>
	inline void MergeSort<K, T>::rozdel(int n, ExplicitQueue<TableItem<K, T>*>* spoj, ExplicitQueue<TableItem<K, T>*>* rozdel1, ExplicitQueue<TableItem<K, T>*>* rozdel2)
	{
		int pocet = 0;
		bool prvy = true;
		while (spoj->size() != 0) {
			if (pocet % n == 0) {
				pocet = 0;
				prvy = !prvy;
			}

			if (prvy) {
				rozdel1->push(spoj->pop());
			}
			else {
				rozdel2->push(spoj->pop());
			}

			pocet++;
		}
	}

	template<typename K, typename T>
	inline void MergeSort<K, T>::spoj(int n, ExplicitQueue<TableItem<K, T>*>* spoj, ExplicitQueue<TableItem<K, T>*>* rozdel1, ExplicitQueue<TableItem<K, T>*>* rozdel2)
	{
		int prvych = 0;
		int druhych = 0;
		K kluc1;
		K kluc2;
		do {
			if (prvych == 0 && druhych == 0) {
				prvych = n < rozdel1->size() ? n : rozdel1->size();
				druhych = n < rozdel2->size() ? n : rozdel2->size();
			}

			if (prvych > 0) {
				kluc1 = (rozdel1->peek())->getKey();
			}

			if (druhych > 0) {
				kluc2 = (rozdel2->peek())->getKey();
			}

			if (kluc1 && kluc2) {
				if (kluc1 < kluc2) {
					prvych--;
					spoj->push(rozdel1->pop());
				}
				else {
					druhych--;
					spoj->push(rozdel2->pop());
				}
			}
			else {
				if (kluc1) {
					prvych--;
					spoj->push(rozdel2->pop());
				}
				else {
					if (kluc2) {
						druhych--;
						spoj->push(rozdel2->pop());
					}
				}
			}
		} while (rozdel1->size() != 0 || rozdel2->size() != 0);
	}
}