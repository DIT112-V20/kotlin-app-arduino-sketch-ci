package platis.solutions.mygithubapp.backend

import platis.solutions.mygithubapp.models.Repository
import retrofit2.Call
import retrofit2.http.GET
import retrofit2.http.Path

interface Endpoint {

    @GET("users/{user}/repos")
    fun getRepositoriesForUsername(@Path("user")username: String): Call<List<Repository>>
}
