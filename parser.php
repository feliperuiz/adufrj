<?php
    if ( $_GET['file'] ) {
        $arquivo = file('/home/felipe/Documents/AD/simulacao-build-desktop/'.$_GET['file'].'.txt');
    }
    
    $requisicoes = array();
    $movimentacoes = array();
    $tempoTotal;
    
    //TODO Calcular variância para todas as métricas para poder gerar intervalo de confiança
    
    foreach ( $arquivo as $linha ) {
        $inicio = strpos($linha, '[');
        $fim = strpos($linha, ']');
        
        if ( $inicio !== FALSE && $fim !== FALSE ) {
            $tempo = (double)trim(substr($linha, $inicio+1, $fim-$inicio-1));
        }
        
        preg_match('/{RQ_(.+?)_(.+?)}/', $linha, $matchesRQ);
        preg_match('/{RT_(.+?)}/', $linha, $matchesRT);
        preg_match('/{IN_(.+?)_(.+?)}/', $linha, $matchesIN);
        
        if ( strpos($linha, '{RQ') !== FALSE) {
            
            $requisicoes[$matchesRQ[2]][$matchesRQ[1]][(string)$tempo] = trim($linha);
        }
        
        if ( strpos($linha, '{RT') !== FALSE) {
            //Temos que ignorar as vezes que tiramos um arquivo da cache 1
            if ( $matchesIN[2] !== null) {
                $movimentacoes[$matchesIN[2]][$matchesRT[1]][(string)$tempo] = array('tipo' => 'out', 'linha' => trim($linha));
            }
        }
        
        if ( strpos($linha, '{IN') !== FALSE) {
            if ( $matchesIN[2] !== null) {
                $movimentacoes[$matchesIN[2]][$matchesIN[1]][(string)$tempo] = array('tipo' => 'in', 'linha' => trim($linha));
            }
        }
        
        if ( strpos($linha, '{FIM}') !== FALSE) {
            $tempoTotal = (double)$tempo;
        }
    }
    
    //Calculando E[Xi2], V[Xi2] e ri2
    $taxaRequisicoes = array();
    $totalRequisicoes = array();
    $mediaIntervaloReq = array();
    $varianciaIntervaloReq = array();
    foreach ( $requisicoes as $idCache => $cacheRQ ) {
        $totalRequisicoes[$idCache] = array();
        $mediaIntervaloReq[$idCache] = array();
        foreach ( $cacheRQ as $idArquivo => $arquivoRQ) {
            $ultimaReq = null;
            $intervaloReq = 0;
            foreach ( $arquivoRQ as $tempo => $RQ ) {
                
                $tempo = (double)$tempo;
                
                if ( $ultimaReq ) {
                    $intervaloReq += $tempo - $ultimaReq;
                }
                $ultimaReq = $tempo;
            }

            $mediaIntervaloReq[$idCache][$idArquivo] = $intervaloReq/(count($arquivoRQ) - 1);
            $totalRequisicoes[$idCache][$idArquivo] = count($arquivoRQ);
            $taxaRequisicoes[$idCache][$idArquivo] = $totalRequisicoes[$idCache][$idArquivo]/$tempoTotal;
            
            $ultimaReq = null;
            $intervaloReq = 0;
            $variancia = 0;
            
            foreach ( $arquivoRQ as $tempo => $RQ ) {
                $tempo = (double)$tempo;
                
                if ( $ultimaReq ) {
                    $intervaloReq = $tempo - $ultimaReq;
                    
                    $variancia += pow( $intervaloReq - $mediaIntervaloReq[$idCache][$idArquivo], 2 );
                }
                $ultimaReq = $tempo;
            }
            $varianciaIntervaloReq[$idCache][$idArquivo] = $variancia/(count($arquivoRQ) - 1 - 1);
        }
        
        ksort($mediaIntervaloReq[$idCache]);
        ksort($varianciaIntervaloReq[$idCache]);
        ksort($totalRequisicoes[$idCache]);
        ksort($taxaRequisicoes[$idCache]);
    }
    
    
    $tempoNaCache = array();
    $porcentagemNaCache = array();
    //Calculando ei2
    foreach ( $movimentacoes as $idCache => $cacheRT ) {
        $tempoNaCache[$idCache] = array();
        $porcentagemNaCache[$idCache] = array();
        foreach ( $cacheRT as $idArquivo => $arquivoRT) {
            $ultimaSaida = 0;
            $ultimaEntrada = 0;
            $tempoAteSair = 0;
            
            $ultimaMovimentacao = end($arquivoRT);
            $tempoUltimaMovimentacao = key($arquivoRT);
            
            //Se última movimentação do arquivo foi uma entrada;
            //Não precisamos levar em conta a última saída, pois sempre calculará corretamente
            if ( $ultimaMovimentacao['tipo'] == 'in' ) {
                //Se entrou no último instante vamos remover a entrada
                if ( $tempoUltimaMovimentacao == (string)$tempoTotal ) {
                    unset($arquivoRT[$tempoUltimaMovimentacao]);
                }
                //Caso tenha entrado antes do tempo final, vamos inserir um evento de saída, para calcular o tempo
                else {
                    $arquivoRT[(string)$tempoTotal] = array('tipo' => 'out', 'linha' => '{FIM}');
                }
            }

            foreach ( $arquivoRT as $tempo => $RT ) {
            
                $tempo = (double)$tempo;
                if ( $RT['tipo'] == 'in' ) {
                    $ultimaEntrada = $tempo;
                    $ultimaSaida = $tempo;
                }
                
                if ( $RT['tipo'] == 'out' ) {
                    $ultimaSaida = $tempo;
                }

                $tempoAteSair += $ultimaSaida-$ultimaEntrada;
            }
            
            $tempoNaCache[$idCache][$idArquivo] = $tempoAteSair;
            $porcentagemNaCache[$idCache][$idArquivo] = $tempoAteSair/$tempoTotal;
        }
        ksort($tempoNaCache[$idCache]);
        ksort($porcentagemNaCache[$idCache]);
    }
    
    var_dump('Total de requisições', $totalRequisicoes);
    var_dump('Taxa de requisições', $taxaRequisicoes);
    var_dump('Tempo na cache', $tempoNaCache);
    var_dump('Porcentagem de tempo na cache', $porcentagemNaCache);
    var_dump('Media de tempo entre chegadas', $mediaIntervaloReq);
    var_dump('Variância de tempo entre chegadas', $varianciaIntervaloReq);
    
    foreach( $taxaRequisicoes[2] as $arquivo => $taxa ) {
        //var_dump(1/$taxa);
    }
    
    var_dump($tempoTotal);
?>
