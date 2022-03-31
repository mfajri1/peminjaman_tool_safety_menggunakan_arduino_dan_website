<!-- proses penyimpanan -->

<?php 
	include "koneksi.php";

	//baca ID data yang akan di edit
	$id = $_GET['id'];

	//baca data karyawan berdasarkan id
	$cari = mysqli_query($konek, "SELECT * FROM t_transaksi WHERE id_transaksi='$id'");
	$hasil = mysqli_fetch_array($cari);


	//jika tombol simpan diklik
	if(isset($_POST['btnSimpan']))
	{
		//baca isi inputan form
		$nokartu = $_POST['nokartu'];
		$jumlah  = $_POST['jumlah'];
		$lemari  = $_POST['lemari'];

		//simpan ke tabel karyawan
		$simpan = mysqli_query($konek, "UPDATE t_transaksi SET tagRfid='$nokartu', jumlah='$jumlah', lemari='$lemari' WHERE id_transaksi='$id'");
		//jika berhasil tersimpan, tampilkan pesan Tersimpan,
		//kembali ke data karyawan
		if($simpan)
		{
			echo "
				<script>
					alert('Tersimpan');
					location.replace('dataTransaksi.php');
				</script>
			";
		}
		else
		{
			echo "
				<script>
					alert('Gagal Tersimpan');
					location.replace('dataTransaksi.php');
				</script>
			";
		}

	}
?>

<!DOCTYPE html>
<html>
<head>
	<?php include "header.php"; ?>
	<title>Edit Data Transaksi</title>
</head>
<body>

	<?php include "menu.php"; ?>

	<!-- isi -->
	<div class="container-fluid">
		<h3>Edit Data Transaksi</h3>

		<!-- form input -->
		<form method="POST">
			<div class="form-group">
				<label>No.Kartu</label>
				<input type="text" name="nokartu" id="nokartu" placeholder="nomor kartu RFID" class="form-control" style="width: 200px" value="<?php echo $hasil['tagRfid']; ?>" readonly>
			</div>
			<div class="form-group">
				<label>Jumlah</label>
				<input type="text" name="jumlah" id="jumlah" placeholder="Jumlah" class="form-control" style="width: 400px" value="<?php echo $hasil['jumlah']; ?>">
			</div>
			<div class="form-group">
				<label>Lemari</label>
				<input type="text" name="lemari" id="lemari" placeholder="Lemari" class="form-control" style="width: 400px" value="<?php echo $hasil['lemari']; ?>">
			</div>
			<button class="btn btn-primary" name="btnSimpan" id="btnSimpan">Simpan</button>
		</form>
	</div>

	<?php include "footer.php"; ?>

</body>
</html>