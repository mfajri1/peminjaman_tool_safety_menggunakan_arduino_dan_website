<!DOCTYPE html>
<html>
<head>
	<?php include "header.php"; ?>
	<title>Data Stock</title>
</head>
<body class="bg-info">

	<?php include "menu.php"; ?>

	<!--isi -->
	<div class="container-fluid">
		<h3 class="text-center" style="font-weight : bold;">Data Stock</h3>
		<a class="btn btn-primary mb-2" href="tambahStock.php" role="button">Tambah Stock</a>
		<br/>
		<br/>
		<table class="table table-bordered">
			<thead>
				<tr class="bg-primary">
					<th style="width: 10px; text-align: center">No.</th>
					<th style="width: 100px; text-align: center">Nama Stock</th>
					<th style="width: 100px; text-align: center">Jumlah Stock</th>
					<th style="width: 100px; text-align: center">Lemari</th>
					<th style="width: 100px; text-align: center">Aksi</th>
				</tr>
			</thead>
			<tbody>

				<?php
					//koneksi ke database
					include "koneksi.php";

					//baca data karyawan
					$sql = mysqli_query($konek, "SELECT * FROM t_stock");
					$no = 0;
					while($data = mysqli_fetch_array($sql))
					{
						$no++;
				?>

				<tr>
					<td> <?php echo $no; ?> </td>
					<td> <?php echo $data['stock_nama']; ?> </td>
					<td> <?php echo $data['stock_jumlah']; ?> </td>
					<td> <?php echo $data['stock_lemari']; ?> </td>
					<td>
						<a href="editStock.php?id=<?php echo $data['stock_id']; ?>"> Edit</a> | <a href="hapusStock.php?id=<?php echo $data['stock_id']; ?>"> Hapus</a>
					</td>
				</tr>
				<?php } ?>
			</tbody>
		</table>

		<!-- tombol tambah data karyawan -->
		<!--<a href="tambah.php"> <button class="btn btn-primary">Tambah Data Karyawan</button> </a>-->
	</div>

	<?php include "footer.php"; ?>

</body>
</html>