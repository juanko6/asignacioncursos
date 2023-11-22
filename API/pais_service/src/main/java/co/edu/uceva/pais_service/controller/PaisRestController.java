package co.edu.uceva.pais_service.controller;

import co.edu.uceva.pais_service.model.entities.Pais;
import co.edu.uceva.pais_service.model.service.IPaisService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/pais-service") //La forma en que llamo el servicio
public class PaisRestController {
    @Autowired
    private IPaisService paisService;

    @GetMapping("/paises")
    public List<Pais> listar(){
        return (List<Pais>) paisService.findAll();
    }

    @PostMapping("/pais")
    public Pais crearPais(@RequestBody Pais pais){
        return paisService.save(pais);
    }

    @PutMapping("/pais")
    public Pais actualizarPais(@RequestBody Pais pais){
        return paisService.save(pais);
    }

    @GetMapping("/hola/{nombre}") //La fomra en que llamo este metodo (ENDPOINT)
    public String holaMundo(@PathVariable("nombre") String nombre){
        return "Hola " + nombre;
    }

}
