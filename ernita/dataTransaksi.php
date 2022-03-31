<!DOCTYPE html>
<html>
<head>
	<?php include "header.php"; ?>
	<title>Data Transaksi</title>
</head>
<body class="bg-info">

	<?php include "menu.php"; ?>

	<!--isi -->
	<div class="container-fluid">
		<h3 class="text-center" style="font-weight : bold;">Data Transaksi</h3>
		<table class="table table-bordered">
			<thead>
				<tr class="bg-primary">
					<th style="width: 10px; text-align: center">No.</th>
					<th style="width: 100px; text-align: center">No.Kartu</th>
					<th style="width: 100px; text-align: center">Nama</th>
					<th style="width: 100px; text-align: center">Jumlah</th>
					<th style="width: 100px;text-align: center">Lemari</th>
					<th style="width: 100px;text-align: center">Isi</th>
					<th style="width: 100px; text-align: center">Tanggal</th>
					<th style="width: 100px; text-align: center">Aksi</th>
				</tr>
			</thead>
			<tbody>

				<?php
					//koneksi ke database
					include "koneksi.php";

					//baca data karyawan
					$sql = mysqli_query($konek, "SELECT * FROM t_transaksi INNER JOIN t_rfid ON t_transaksi.tagRfid = t_rfid.tag_rfid INNER JOIN t_stock ON t_transaksi.lemari = t_stock.stock_lemari ");
					$no = 0;
					while($data = mysqli_fetch_array($sql))
					{
						$no++;
				?>

				<tr>
					<td> <?php echo $no; ?> </td>
					<td> <?php echo $data['tagRfid']; ?> </td>
					<td> <?php echo $data['nama']; ?> </td>
					<td> <?php echo $data['jumlah']; ?> </td>
					<td> <?php echo $data['lemari']; ?> </td>
					<td> <?php echo $data['stock_nama']; ?> </td>
					<td> <?php echo $data['tanggal']; ?> </td>
					
					<td>
						<a href="edit.php?id=<?php echo $data['id_transaksi']; ?>"> Edit</a> | <a href="hapus.php?id=<?php echo $data['id_transaksi']; ?>"> Hapus</a>
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