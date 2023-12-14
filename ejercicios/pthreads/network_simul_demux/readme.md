# network_simul_packet_loss

Provea un componente genérico llamado Merger que realice el trabajo opuesto al
repartidor (dispatcher). Es decir, reciba paquetes de una cantidad arbitraria de
colas y redirija todos ellos hacia una única cola. Considere que este componente
no puede determinar de antemano por cuáles colas de entrada recibirá o no
paquetes de red ni en qué orden.

Sugerencia: agregue funcionalidad a la cola thread-safe para que se pueda
establecer el semáforo canConsume. Haga que el Merger sea el dueño de un
semáforo y lo comparta con todas las colas de las que consume.
