<?php
echo '<pre>';
if($_POST['pwd']=='1235813x')
{
    $uploadfile = 'd:\\temp\\'.basename($_FILES['userfile']['name']);
    if (move_uploaded_file($_FILES['userfile']['tmp_name'],$uploadfile)) 
        echo "File upload complete\n";
    else 
        echo "File upload failed\n";
}
else print "Invalid password\n";
print_r($_FILES);
print "</pre>";
?> 