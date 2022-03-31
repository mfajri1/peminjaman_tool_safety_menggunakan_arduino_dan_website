<!-- proses penyimpanan -->

<?php 
	include "koneksi.php";

	//baca ID data yang akan di edit
	$id = $_GET['id'];

	//baca data karyawan berdasarkan id
	$cari = mysqli_query($konek, "SELECT * FROM t_rfid WHERE id='$id'");
	$hasil = mysqli_fetch_array($cari);


	//jika tombol simpan diklik
	if(isset($_POST['btnSimpan']))
	{
		//baca isi inputan form
		$tag	= $_POST['tag'];
		$nama 	= $_POST['nama'];
		$pass  	= $_POST['pass'];
		$stat 	= $_POST['stat'];

		//simpan ke tabel karyawan
		$simpan = mysqli_query($konek, "UPDATE t_rfid SET tag_rfid='$tag', nama='$nama', pass='$pass', stat='$stat' WHERE id='$id'");
		//jika berhasil tersimpan, tampilkan pesan Tersimpan,
		//kembali ke data karyawan
		if($simpan)
		{
			echo "
				<script>
					alert('Tersimpan');
					location.replace('dataPegawai.php');
				</script>
			";
		}
		else
		{
			echo "
				<script>
					alert('Gagal Tersimpan');
					location.replace('dataPegawai.php');
				</script>
			";
		}

	}
?>

<!DOCTYPE html>
<html>
<head>
	<?php include "header.php"; ?>
	<title>Edit Data Pegawai</title>
</head>
<body class="bg-info">

	<?php include "menu.php"; ?>

	<!-- isi -->
	<div class="container-fluid">
		<h3 style="font-weight:bold">Edit Data Pegawai</h3>

		<!-- form input -->
		<form method="POST">
			<div class="form-group">
				<label>Tag Rfid</label>
				<input type="text" name="tag" id="nokartu" placeholder="Tag Rfid" class="form-control" style="width: 300px" value="<?php echo $hasil['tag_rfid']; ?>" readonly>
			</div>
			<div class="form-group">
				<label>Nama</label>
				<input type="text" name="nama" id="jumlah" placeholder="Nama Pegawai" class="form-control" style="width: 300px" value="<?php echo $hasil['nama']; ?>">
			</div>
			<div class="form-group">
				<label>Password</label>
				<input type="password" name="pass" id="lemari" placeholder="Password" class="form-control" style="width: 300px" value="<?php echo $hasil['pass']; ?>">
			</div>
			<div class="form-group">
				<label for="disabledSelect">Pilih Status</label>
				<select style="width: 300px" class="form-control" name="stat">
					<option>Pilih Status</option>
					<option value="A" <?= $hasil['stat'] == 'A'? "selected" : ""; ?>>Aktif</option>
					<option value="N" <?= $hasil['stat'] == 'N'? "selected" : ""; ?>>Nonaktif</option>
				</select>
			</div>
			<button class="btn btn-primary" style="width: 300px" name="btnSimpan" id="btnSimpan">Simpan</button>
		</form>
	</div>


</body>
</html>