<!-- proses penyimpanan -->

<?php 
	include "koneksi.php";

	//baca ID data yang akan di edit
	$id = $_GET['id'];

	//baca data karyawan berdasarkan id
	$cari = mysqli_query($konek, "SELECT * FROM t_stock WHERE stock_id='$id'");
	$hasil = mysqli_fetch_array($cari);


	//jika tombol simpan diklik
	if(isset($_POST['btnSimpan']))
	{
		//baca isi inputan form
		$stock_nama 	= $_POST['stock_nama'];
		$stock_jumlah 	= $_POST['stock_jumlah'];
		$stock_lemari  	= $_POST['stock_lemari'];

		//simpan ke tabel karyawan
		$simpan = mysqli_query($konek, "UPDATE t_stock SET stock_nama='$stock_nama', stock_jumlah='$stock_jumlah', stock_lemari='$stock_lemari' WHERE stock_id='$id'");
		//jika berhasil tersimpan, tampilkan pesan Tersimpan,
		//kembali ke data karyawan
		if($simpan)
		{
			echo "
				<script>
					alert('Tersimpan');
					location.replace('dataStock.php');
				</script>
			";
		}
		else
		{
			echo "
				<script>
					alert('Gagal Tersimpan');
					location.replace('dataStock.php');
				</script>
			";
		}

	}
?>

<!DOCTYPE html>
<html>
<head>
	<?php include "header.php"; ?>
	<title>Edit Data Stock</title>
</head>
<body class="bg-info">

	<?php include "menu.php"; ?>

	<!-- isi -->
	<div class="container-fluid">
		<h3 style="font-weight:bold">Edit Data Stock</h3>

		<!-- form input -->
		<form method="POST">
			<div class="row">
				<div class="col-sm-3">
					<div class="form-group">
						<label>Nama</label>
						<input type="text" name="stock_nama" id="nama" placeholder="Nama Stock" class="form-control" value="<?= $hasil['stock_nama']?>">
					</div>
				</div>
				<div class="col-sm-3">
					<div class="form-group">
						<label>Jumlah</label>
						<div class="input-group">
							<input type="text" name="stock_jumlah" id="nama" placeholder="Jumlah Stock" class="form-control" aria-describedby="basic-addon1" value="<?= $hasil['stock_jumlah']?>">
							<span class="input-group-addon" id="basic-addon1">Pcs</span>
						</div>
					</div>
				</div>
				<div class="col-sm-3">
					<div class="form-group">
						<label>Lemari</label>
						<div class="input-group">
							<span class="input-group-addon" id="basic-addon2">No</span>
							<input type="text" name="stock_lemari" id="nama" placeholder="Lemari No" class="form-control" aria-describedby="basic-addon2" value="<?= $hasil['stock_lemari']?>">
						</div>
					</div>
				</div>
				<div class="col-sm-1">
					<div class="form-group">
						<label style="color-white">-</label>
						<button class="btn btn-primary" name="btnSimpan" id="btnSimpan">Simpan</button>
					</div>
				</div>
			</div>
		</form>
	</div>


</body>
</html>