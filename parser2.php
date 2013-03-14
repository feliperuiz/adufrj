<?php
    $arquivo = file('/home/felipe/Documents/AD/simulacao-build-desktop/'.$_GET['file'].'.txt');
    
    $somaCustos = 0;
    $totalCustos = 0;
    foreach ( $arquivo as $linha ) {
        preg_match('/(\d+)/', $linha, $custo);
        $somaCustos += $custo[0];
        ++$totalCustos;
    }
    
    $mediaCusto = $somaCustos/$totalCustos;
    
    var_dump($mediaCusto);

?>
