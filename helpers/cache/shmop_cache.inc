<?php
namespace Cache;

class shmop_cache 
{
	const ENTRY_DELIMITER = '/==/';
	const KV_DELIMITER = '<==>';
	const FILE_MODE = 0600;
	const BULK_SIZE = 10000;

	public static function get($key, $initialize, $update = null) 
	{
		$shmkey = self::hash($key);
		$shmid = self::open($shmkey);
		$data = self::retrieve($shmid);
		if (!isset($data[$key]))
			return self::cache($shmid, $data, $key, $initialize());
		$value = $data[$key];
		if ($update) 
			return self::cache($shmid, $data, $key, $update($value));
		return $value;
	}

	private static function hash($str) 
	{
		return abs(crc32($str)) % 64;
	}

	private static function open($shmkey) 
	{
		return shmop_open($shmkey, 'c', shmop_cache::FILE_MODE, shmop_cache::BULK_SIZE);
	}

	private static function retrieve($shmid) 
	{
		$bulk = shmop_read($shmid, 0, self::BULK_SIZE);
		$serial_data = self::str_from_mem($bulk);
		$data = self::deserialize($serial_data);
		return $data;
	}

	private static function cache($shmid, $data, $key, $value) 
	{
		$data[$key] = $value;
		self::store($shmid, $data);
		return $value;
	}

	private static function store($shmid, $data)
	{
		$serial_data = self::serialize($data);
		shmop_write($shmid, "$serial_data\0", 0);
	}

	private static function serialize($data) 
	{
		$serial_data = '';
		foreach ($data as $key => $value) {
			if ($serial_data)
				$serial_data .= shmop_cache::ENTRY_DELIMITER;
			$serial_data .= $key . shmop_cache::KV_DELIMITER . $value;
		}
		return $serial_data;
	}

	private static function deserialize($serial_data) 
	{
		$kv_pairs = explode(shmop_cache::ENTRY_DELIMITER, $serial_data);
		$data = array();
		foreach ($kv_pairs as $kv_pair) {
			$tuple = explode(shmop_cache::KV_DELIMITER, $kv_pair);
			if (count($tuple) == 2) 
				$data[$tuple[0]] = $tuple[1];
		}
		return $data;
	}

	private static function str_from_mem($str) 
	{
	 	$end_pos = strpos($str, "\0");
	 	if ($end_pos === false)
	 		throw new \Exception("Data overflow in memory block. Increase BULK_SIZE and redeploy: $str");
		return substr($str, 0, $end_pos);
	}
}
?>