<!DOCTYPE html>
<html>
<head>
	<?php include "header.php"; ?>
	<title>Data Pegawai</title>
</head>
<body class="bg-info">

	<?php include "menu.php"; ?>

	<!--isi -->
	<div class="container-fluid">
		<h3 class="text-center" style="font-weight : bold;">Data Pegawai</h3>
		<a class="btn btn-primary mb-2" href="tambah.php" role="button">Tambah Pegawai</a>
		<br/>
		<br/>
		<table class="table table-bordered">
			<thead>
				<tr class="bg-primary">
					<th style="width: 10px; text-align: center">No.</th>
					<th style="width: 100px; text-align: center">Tag Rfid</th>
					<th style="width: 100px; text-align: center">Nama</th>
					<th style="width: 100px; text-align: center">Password</th>
					<th style="width: 100px; text-align: center">Status</th>
					<th style="width: 100px; text-align: center">Aksi</th>
				</tr>
			</thead>
			<tbody>

				<?php
					//koneksi ke database
					include "koneksi.php";

					//baca data karyawan
					$sql = mysqli_query($konek, "SELECT * FROM t_rfid");
					$no = 0;
					while($data = mysqli_fetch_array($sql))
					{
						$no++;
				?>

				<tr>
					<td> <?php echo $no; ?> </td>
					<td> <?php echo $data['tag_rfid']; ?> </td>
					<td> <?php echo $data['nama']; ?> </td>
					<td> <?php echo $data['pass']; ?> </td>
					<td> <?php echo $data['stat']; ?> </td>
					<td>
						<a href="editPegawai.php?id=<?php echo $data['id']; ?>"> Edit</a> | <a href="hapusPegawai.php?id=<?php echo $data['id']; ?>"> Hapus</a>
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