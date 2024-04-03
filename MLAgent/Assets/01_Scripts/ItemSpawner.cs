using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemSpawner : MonoBehaviour
{
	[SerializeField] private GameObject goodItem;
	[SerializeField] private GameObject badItem;

	public int goodItemCnt = 30;
	public int badItemCnt = 10;

	private List<GameObject> goodItemList = new List<GameObject>();
	private List<GameObject> badItemList = new List<GameObject>();

	public void SpawnItems()
	{
		foreach (GameObject o in goodItemList)
		{
			Destroy(o);
		}
		foreach (GameObject o in badItemList)
		{
			Destroy(o);
		}

		goodItemList.Clear();
		badItemList.Clear();

		for (int i = 0; i < goodItemCnt; i++)
		{
			Vector3 position = new Vector3(Random.Range(-23f, 23f), 0.05f, Random.Range(-23f, 23f));
			Quaternion rotation = Quaternion.Euler(Vector3.up * Random.Range(0, 360));
			goodItemList.Add(Instantiate(goodItem, transform.position + position, rotation));
		}

		for (int i = 0; i < badItemCnt; i++)
		{
			Vector3 position = new Vector3(Random.Range(-23f, 23f), 0.05f, Random.Range(-23f, 23f));
			Quaternion rotation = Quaternion.Euler(Vector3.up * Random.Range(0, 360));
			goodItemList.Add(Instantiate(badItem, transform.position + position, rotation));
		}
	}

	private void Update()
	{
		if (Input.GetMouseButtonDown(0))
		{
			SpawnItems();
		}
	}
}
